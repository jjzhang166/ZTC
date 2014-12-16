#ifndef ZTC_CLIENTNET_ZCONFING_H
#define ZTC_CLIENTNET_ZCONFING_H

#include "../include/ZMacroDefine.h"
#include "../include/ZType.h"

//头文件包含
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <map>
#include <queue>
#include <vector>
#include <hash_map>
#include <stdarg.h>

#ifdef _MSC_VER
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#include <Windows.h>
#ifdef _WIN32_WCE
	#pragma comment(lib, "ws2.lib")
#else
	#pragma comment(lib, "Ws2_32.lib")
#endif
	#define Hash_map stdext::hash_map
	#define snprintf _snprintf
#elif __GNUC__
	#include <sys/time.h>
	#include <stdint.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <iconv.h>
	#include <pthread.h>
	#include <netdb.h>
	#include <semaphore.h>
	#define Hash_map __gnu_cxx::hash_map
#endif

BEGIN_ZTC_NAMESPACE
//类型定义

#ifdef _MSC_VER
	typedef SOCKET Socket_handle;
	#define close_socket closesocket
#else
	typedef int Socket_handle;
	#define INVALID_SOCKET 0
	#define close_socket close
	#define SOCKET_ERROR -1
#endif

#define INVALID_VALUE 0XFFFF
#define MAX_PATH_LEN 260

/*
客户端网络模块配置，实用宏定义
*/

#define MAX_TCP_MSG_LEN (0xFFFF + 8)
#define MAX_UDP_MSG_LEN (0xFFFF + 6)

/*
TCP消息的结构,消息长度为消息体长度
--------------------------------------------------------------------------------
|消息类型|     消息ID     |消息长度 |           消息体
| 2字节	 |     4字节      | 2字节   |  长度为消息长度-前面三部分之和
--------------------------------------------------------------------------------
*/

/*
UDP消息的结构,消息长度为整个消息包长度
-----------------------------------------------------------------------
|消息类型|     消息ID     |           消息体
| 2字节	 |     4字节      |  长度为消息长度-前面三部分之和
-----------------------------------------------------------------------
*/

// 消息类型偏移量
#define OFFSET_MSG_TYPE 0
// 消息类型所占长度
#define LEN_MSG_TYPE sizeof(uint16_t)

// 消息ID偏移量
#define OFFSET_MSG_ID LEN_MSG_TYPE
// 消息ID所占长度
#define LEN_MSG_ID sizeof(uint32_t)

// 这里的消息长度包含消息头长度，也就是整个消息包长度
// 消息长度偏移量
#define OFFSET_MSG_LEN (LEN_MSG_TYPE + LEN_MSG_ID)
// 消息长度所占长度
#define LEN_MSG_LEN sizeof(uint16_t)

// 消息头部的长度
#define LEN_TCP_MSG_HEAD (LEN_MSG_TYPE + LEN_MSG_ID + LEN_MSG_LEN)
#define LEN_UDP_MSG_HEAD (LEN_MSG_TYPE + LEN_MSG_ID)

// 消息体偏移量
#define OFFSET_TCP_MSG_BODY (LEN_TCP_MSG_HEAD)
#define OFFSET_UDP_MSG_BODY (LEN_UDP_MSG_HEAD)

END_ZTC_NAMESPACE
#endif //ZTC_CLIENTNET_ZCONFING_H