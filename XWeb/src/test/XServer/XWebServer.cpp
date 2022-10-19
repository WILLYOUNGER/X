#include "XWebServer.h"
#include "./XUtils/XUtils.h"
#include "./XLog/XLog.h"
#include <sys/epoll.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
using namespace XNETBASE;
using namespace XNETSTRUCT;
using namespace XUTILSTOOL;

XWebServer::XWebServer(std::string ip, int port)
{
    init(ip, port);
}

void XWebServer::init(string ip, int port)
{
    pool = new XPthreadPool<XMsgPtr, XHttp>(8, 10000);
    XServerBase::init(ip, port);
}

void XWebServer::ConnectCallback(XSocket socket)
{
    //XLOG_DEBUG("a client connected.connfd: ", to_string(socket).c_str());
}

void XWebServer::CloseCallback(void)
{
}

void XWebServer::ReadCallback(XMsgPtr msg)
{
    pool->append(msg);
    XLOG_INFO("%s", msg->getContent().c_str());
}

bool XWebServer::WriteCallback(XSocket epollfd, XSocket socket)
{
    if (XWebServer::m_reply.count(socket) == 0)
    {
        NETUTILS->modfd(epollfd, socket, EPOLLIN, 0);
        return true;
    }
    else
    {
        auto temp = m_reply[socket]->front();

        if (temp.isEmpty() == false)
        {
            struct iovec _iv[2];
            int _iv_count;
            char* _head = (char*)malloc((temp.getHeadString().size() + 1) * sizeof(char));
            char* _content = (char*)malloc((temp.getContentLength() + 1) * sizeof(char));
            strncpy(_head, temp.getHeadString().c_str(), temp.getHeadString().size());
            _iv[0].iov_base = _head;
            _iv[0].iov_len = temp.getHeadString().size();
            if (temp.contentIsFile())
            {
                _iv[1].iov_base = temp.getFileAddress();
            }
            else
            {
                strncpy(_content, temp.getContent().c_str(), temp.getContent().size());
                _content[temp.getContent().size()] = '\0';
                _iv[1].iov_base = _content;
            }
            
            _iv[1].iov_len = temp.getContentLength();
            _iv_count = 2;
            int bytes_to_send = _iv[0].iov_len + _iv[1].iov_len;
            int bytes_have_send = 0;

            _head[temp.getHeadString().size()] = '\0';

            int templen = writev(socket, _iv, _iv_count);
            if (templen < 0)
            {
                if (errno == EAGAIN)
                {
                    NETUTILS->modfd(epollfd, socket, EPOLLOUT, 0);
                }
            }
            else
            {

            }
            XLOG_INFO("%s", _head);
            //XLOG_INFO("%s", _content);
            free(_head);
            free(_content);

            XWebServer::m_reply[socket]->pop_front();
            NETUTILS->modfd(epollfd, socket, EPOLLIN, 0);

            return temp.getNeedClose();
        }
        else
        {
            return true;
        }
    }
}