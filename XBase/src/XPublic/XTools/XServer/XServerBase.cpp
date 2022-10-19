#include "XServerBase.h"
#include "XUtils.h"
#include "XLog.h"
#ifdef __LINUX
#include <sys/epoll.h>
#endif
#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
using namespace XNETBASE;
using namespace XNETSTRUCT;
using namespace XUTILSTOOL;

std::map<XSocket, std::list<XResponse>*> XServerBase::m_reply;

XServerBase::XServerBase()
{
    XLOG_INFO("do nothing.");
}

XServerBase::XServerBase(string ip, int port)
{
    init(ip, port);
}

void XServerBase::init(string ip, int port)
{
    m_xserver_server = new XServer(ip.c_str(), port);
	auto connCb = bind(&XServerBase::ConnectCallback,this,std::placeholders::_1);
    m_xserver_server->setConnectionCallback(connCb);

    auto closeCb = bind(&XServerBase::CloseCallback, this);
    m_xserver_server->setCloseCallback(closeCb);

    auto readCb = bind(&XServerBase::ReadCallback,this,std::placeholders::_1);
    m_xserver_server->setReadCallback(readCb);

    auto writeCb = bind(&XServerBase::WriteCallback, this, std::placeholders::_1, std::placeholders::_2);
    m_xserver_server->setWriteCallback(writeCb);

    m_xserver_server->beginListen();
}

void XServerBase::ConnectCallback(XSocket socket)
{
    XLOG_INFO("a client connect.");
}

void XServerBase::CloseCallback(void)
{
    XLOG_INFO("a client close.");
}

void XServerBase::ReadCallback(XMsgPtr msg)
{
    XLOG_INFO("rev a msg from a client.");
}

bool XServerBase::WriteCallback(XSocket epollfd, XSocket socket)
{
    XLOG_INFO("send a msg to a client");
    return true;
}

void XServerBase::TimeOutCallback(XSocket socket)
{
    XLOG_INFO("socket:%d time out!", socket);
}
