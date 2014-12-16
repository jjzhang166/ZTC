/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZClientSocket.h
* File Identifier :
* Abstract        : 提供基本的阻塞的TCP, UDP服务
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.10.26 19:10:53
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.10.26 19:10:53
*/

#ifndef ZTC_CLIENTNET_ZCLIENTSOCKET_H
#define ZTC_CLIENTNET_ZCLIENTSOCKET_H

#include "../include/ZMacroDefine.h"
#include "ZConfig.h"

BEGIN_ZTC_NAMESPACE

/*
阻塞的Tcp服务
*/
class ZTC_CLASS ZBtcp
{
public:
	ZBtcp();
	virtual ~ZBtcp();

	int connect(const char* ip, unsigned short port);
	int connect(unsigned int ip, unsigned short port);
	int connect(unsigned int ip, unsigned short port, int timeout);
	int disconnect();

	/* timeout说明:
	 * timeout单位为秒
	 * time > 0 为正常的超时设置, 在限定时间内如果没有正常返回, 到了设定的时间会超时返回
	 * time == 0 表示无超时设置, 会一直阻塞直到操作完成或者出错才返回
	 * time < 0 表示这次操作会执行一次立刻返回, 可能成功也可能失败.
	 */
	int send(const char* pData, int len);
	int send(const char* buf, int len, int timeout);
	int recv(char* buf, int len);
	int recv(char* buf, int len, int timeout);
	int recv_whole(char* buf, int len);	//len长度全部读取完才返回. 若成功返回值和len相等, 失败返回-1
	int recv_whole(char* buf, int len, int timeout); //在规定时间内返回值和timeout相等则成功, 否则失败

private:
	SOCKET m_socket;
	sockaddr_in m_addr;
};

/*
阻塞的UDP服务
*/
class ZTC_CLASS ZBudp
{
public:
	ZBudp(const char* ip, unsigned int port);
	virtual ~ZBudp();

	int send(const char* pData, int len, int timeout = -1);	//timeout单位毫秒, <0表示无超时限制
	int recv(char* buf, int len, int timeout = -1);	//timeout单位毫秒, <0表示无超时限制

	SOCKET m_socket;

private:
	//SOCKET m_socket;
	sockaddr_in m_addr;
};

END_ZTC_NAMESPACE
#endif //ZTC_CLIENTNET_ZCLIENTSOCKET_H