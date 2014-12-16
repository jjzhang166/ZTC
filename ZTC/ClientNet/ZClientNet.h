/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZClientNet.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.9.25 20:14:31
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.9.25 20:14:31
*/

#ifndef ZTC_CLIENTNET_ZCLIENTNET_H
#define ZTC_CLIENTNET_ZCLIENTNET_H

#include "../include/ZMacroDefine.h"
#include "ZConfig.h"

BEGIN_ZTC_NAMESPACE

//连接状态
enum ConnectState
{
	Unconnected, //未连接
	Connecting, //连接中
	Connected //已经连接
};

/*
Tcp服务，与服务器的一条连接，提供连接上的所有操作
*/
class ZITcp
{
public:
	virtual ~ZITcp(){}
	//连接服务器，异步
	virtual int connect(const char *pIP, uint16_t port) = 0;
	virtual int connect(uint32_t ip, uint16_t port) = 0;
	//断开连接，同步
	virtual int disconnect() = 0;
	//重连，异步
	virtual int reconnect() = 0;
	//是否连接上了
	virtual bool isConnected() = 0;
	//当前状态
	virtual ConnectState state() = 0;
	//发送消息
	virtual int send(const char* pData, uint32_t len) = 0;
	virtual int send(uint16_t msgType, uint32_t msgID, const char* pMsg, uint32_t msgLen) = 0;
	//获取接收到的消息
	virtual int frontMsg(const char** pMsg, uint32_t* len) = 0;
	//消息出队
	virtual int popMsg() = 0;
};


//UDP 连接
class ZIUdp
{
public:
	virtual ~ZIUdp(){}
	//初始化
	virtual int open(const char* ip, uint16_t port) = 0;
	virtual int open(const char* ip, const char* port) = 0;
	//关闭
	virtual int close() = 0;
	//发送消息
	virtual int send(const char* pData, uint32_t len) = 0;
	virtual int send(uint16_t msgType, uint32_t msgID, const char* pMsg, uint32_t msgLen) = 0;
	//获取接收到的消息
	virtual int frontMsg(const char** pMsg, uint32_t* len) = 0;
	//消息出队
	virtual int popMsg() = 0;
};

/*
网络框架,提供网络底层服务
*/
class ZINetFrame
{
public:
	virtual ~ZINetFrame(){}
	//分发网络事件
	virtual int dispatch() = 0;
	//创建，销毁tcp连接
	virtual ZITcp* create_tcp() = 0;
	virtual void release_tcp(ZITcp* pTcp) = 0;
	//创建，销毁udp服务
	virtual ZIUdp* create_udp() = 0;
	virtual void release_udp(ZIUdp* pUdp) = 0;

};

//创建销毁网络框架的接口
ZTC_API ZINetFrame* create_net_frame();
ZTC_API void release_net_frame(ZINetFrame* pFrame);
ZTC_API uint16_t ntohs(const void* data);
ZTC_API uint32_t ntohl(const void* data);

END_ZTC_NAMESPACE

#endif //ZTC_CLIENTNET_ZCLIENTNET_H