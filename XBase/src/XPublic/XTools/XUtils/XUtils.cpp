#include "XUtils.h"

#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>	//close(int sockfd)
#include <cstring>
#include <chrono>
#include <ctime>
#include <time.h>

#ifdef __LINUX
#include <sys/epoll.h>
#endif

using namespace std;
using namespace XUTILSTOOL;
using namespace XNETSTRUCT;

NetUtils* NetUtils::m_netUtils_instance = nullptr;

NetUtils* NetUtils::getInstance()
{
	if (m_netUtils_instance == nullptr)
	{
		m_netUtils_instance->init();
	}
	return m_netUtils_instance;
}

NetUtils::~NetUtils()
{
}

NetUtils::NetUtils()
{
}

void NetUtils::init()
{
}

int NetUtils::setnonblocking(XSocket fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option |= O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void NetUtils::addfd(XSocket epollfd, XSocket fd, bool one_shot, int mode)
{
#ifdef __LINUX
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLRDHUP;
	if (one_shot)
	{
		event.events |= EPOLLONESHOT;
	}
	if (mode == 1)
	{
		event.events |= EPOLLET;
	}
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
#endif
}

void NetUtils::removefd(XSocket epollfd, XSocket fd)
{
#ifdef __LINUX
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
	close(fd);
#endif
}

void NetUtils::modfd(XSocket epollfd, XSocket fd, int ev, int mode)
{
#ifdef __LINUX
	epoll_event event;
	event.data.fd = fd;
    if (1 == mode)
        event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    else
        event.events = ev | EPOLLONESHOT | EPOLLRDHUP;

    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
#endif
}

void NetUtils::addsig(int sig, void (handler)(int), bool restart)
{
	struct sigaction sa;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = handler;
	if (restart)
	{
		sa.sa_flags |= SA_RESTART;
	}
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig, &sa, NULL) != -1);
}

void NetUtils::senderror(XSocket connfd, const char* info)
{
	XLOG_ERROR("%s", info);
	send(connfd, info, strlen(info), 0);
	close(connfd);
}

void NetUtils::setFdCloseType(XNETSTRUCT::XSocket fd, int isCloseNow, int time)
{
	struct linger tmp = {isCloseNow, time};
        setsockopt(fd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
}
