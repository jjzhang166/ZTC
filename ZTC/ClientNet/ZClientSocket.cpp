#include "ZClientSocket.h"
#include "ZClientTimer.h"

/*
提供基本的阻塞的TCP, UDP服务
*/

BEGIN_ZTC_NAMESPACE

/*
阻塞的Tcp服务
*/
ZBtcp::ZBtcp(): m_socket(-1)
{
}

ZBtcp::~ZBtcp()
{
	if (m_socket != -1)
	{
		closesocket(m_socket);
		m_socket = -1;
	}
}

int ZBtcp::connect(const char* ip, unsigned short port)
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	m_addr.sin_addr.s_addr = inet_addr(ip);
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;

	return ::connect(m_socket, (struct sockaddr*)&m_addr, sizeof(m_addr));
}

int ZBtcp::connect(unsigned int ip, unsigned short port)
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	m_addr.sin_addr.s_addr = ip;
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;

	return ::connect(m_socket, (struct sockaddr*)&m_addr, sizeof(m_addr));
}

int ZBtcp::connect(unsigned int ip, unsigned short port, int timeout)
{
	int error = -1;
	int len = sizeof(int);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket < 0)
	{
		return -1;
	}

	m_addr.sin_addr.s_addr = ip;
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;

	unsigned long ul = 1;
	ioctlsocket(m_socket, FIONBIO, &ul); //设置为非阻塞模式

	bool success = false;

	if(0 == ::connect(m_socket, (struct sockaddr *)&m_addr, sizeof(m_addr)))
	{
		success = true;
	}
	else
	{
		timeval tm;
		tm.tv_sec  = timeout / 1000;
		tm.tv_usec = timeout % 1000;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(m_socket, &set);

		if(::select(m_socket+1, NULL, &set, NULL, &tm) > 0)
		{
			int error = -1;
			int len = sizeof(int);

			getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char *)&error, /*(socklen_t *)*/&len);
			if(0 == error) 
			{
				ul = 0;
				ioctlsocket(m_socket, FIONBIO, &ul); //设置为阻塞模式

				success = true;
			}
		} 
	}

	if(!success) 
	{
		closesocket(m_socket);
		m_socket = -1;
		return -1;
	}

	return 0;
}

int ZBtcp::disconnect()
{
	int ret = 0;

	if (m_socket != -1)
	{
		int ret = closesocket(m_socket);
		m_socket = -1;
	}

	return ret;
}

int ZBtcp::send(const char* buf, int len)
{
	return ::send(m_socket, buf, len, 0);
}

int ZBtcp::send(const char* buf, int len, int timeout)
{
	timeval tm;
	tm.tv_sec  = timeout / 1000;
	tm.tv_usec = timeout % 1000;

	fd_set WriteSet;
	FD_ZERO(&WriteSet);
	FD_SET(m_socket, &WriteSet);

	int ret = select(0, NULL, &WriteSet, NULL, &tm);
	if(ret > 0)
	{
		ret = ::send(m_socket, buf, len, 0);
	}

	return ret;
}

int ZBtcp::recv(char* buf, int len)
{
	return ::recv(m_socket, buf, len, 0);
}

int ZBtcp::recv(char* buf, int len, int timeout)
{
	timeval tm;
	tm.tv_sec  = timeout / 1000;
	tm.tv_usec = timeout % 1000;

	fd_set ReadSet;
	FD_ZERO(&ReadSet);
	FD_SET(m_socket, &ReadSet);

	int ret = select(0, &ReadSet, NULL, NULL, &tm);
	if(ret > 0)
	{
		ret = ::recv(m_socket, buf, len, 0);
	}

	return ret;
}

int ZBtcp::recv_whole(char* buf, int len)
{
	if (NULL == buf)
	{
		return -1;
	}

	int pos = 0;
	int ret = 0;

	while (pos < len)
	{
		ret = ::recv(m_socket, buf + pos, len - pos, 0);
		if (ret <= 0)
		{
			return -1;
		}

		pos += ret;
	} 

	return pos;
}

int ZBtcp::recv_whole(char* buf, int len, int timeout)
{
	if (NULL == buf || len < 0)
	{
		return -1;
	}

	int pos = 0;
	int ret = 0;

	if (timeout > 0)
	{
		uint32_t begin_time = get_time_ms();
		uint32_t cur_time;
		int32_t  new_timeout;

		while (pos < len)
		{
			cur_time = get_time_ms();
			if ((new_timeout = timeout - (cur_time - begin_time)) <= 0)
			{
				return -1;
			}

			ret = this->recv(buf + pos, len - pos, new_timeout);
			if (ret <= 0)
			{
				return -1;
			}

			pos += ret;
		} 

		ret = pos;
	} 
	else if (timeout < 0)	//表示如果一次瞬时性的接收试探. 能收到全部数据, 则返回成功, 否则失败.
	{
		ret = this->recv(buf, len, timeout);
		if (ret != len)
		{
			return -1;
		}
	}
	else //timeout == 0 表示一直阻塞, 直到所有数据接收完毕.
	{
		while (pos < len)
		{
			ret = this->recv(buf + pos, len - pos);
			if (ret <= 0)
			{
				return -1;
			}

			pos += ret;
		} 

		ret = pos;
	}

	return ret;
}


/*
阻塞的UDP服务
*/
ZBudp::ZBudp(const char* ip, unsigned int port)
{
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);

	m_addr.sin_addr.s_addr = inet_addr(ip);
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;
}

ZBudp::~ZBudp()
{
	closesocket(m_socket);
}

int ZBudp::send(const char* buf, int len, int timeout)
{
	int ret = 0;

	if (timeout >= 0)
	{
		timeval tm;
		tm.tv_sec  = timeout / 1000;
		tm.tv_usec = timeout % 1000;

		fd_set WriteSet;
		FD_ZERO(&WriteSet);
		FD_SET(m_socket, &WriteSet);

		ret = select(m_socket+1, NULL, &WriteSet, NULL, &tm);
		if(ret > 0)
		{
			ret = ::sendto(m_socket, buf, len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
		}
	}
	else
	{
		ret = ::sendto(m_socket, buf, len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
	}

	return ret;
}

int ZBudp::recv(char* buf, int len, int timeout)
{
	int ret = 0;

	if (timeout >= 0)
	{
		timeval tm;
		tm.tv_sec  = timeout / 1000;
		tm.tv_usec = timeout % 1000;

		fd_set ReadSet;
		FD_ZERO(&ReadSet);
		FD_SET(m_socket, &ReadSet);

		ret = select(m_socket+1, &ReadSet, NULL, NULL, &tm);
		if(ret > 0)
		{
			int addr_len = sizeof(m_addr);
			ret = ::recvfrom(m_socket, buf, len, 0, (struct sockaddr*)&m_addr, &addr_len);
		}
	}
	else
	{
		int addr_len = sizeof(m_addr);
		ret = ::recvfrom(m_socket, buf, len, 0, (struct sockaddr*)&m_addr, &addr_len);
	}

	return ret;
}

END_ZTC_NAMESPACE