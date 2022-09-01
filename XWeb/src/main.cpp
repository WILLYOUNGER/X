#include <iostream>

#include "XBaseNet.h"
#include "XWebServer.h"
#include "XLog/XLog.h"
#include "XFile.h"
#include "XMysql.h"
//#include <Config.h>
#include "muduo/net/EventLoop.h"

#include "Echo.h"

#include <unistd.h>

using namespace std;
using namespace XNETBASE;
using namespace XFILETOOL;
using namespace XSQLTOOL;
int main(int argc, char* argv[])
{
	if (!XLOG->init("XWebLog.txt", 1))
	{
		return 0;
	}

	//XLOG_INFO("%s, version: %d.%d.%d", argv[0], XWEB_VERSION_MAJOR, XWEB_VERSION_MINOR, XWEB_VERSION_PATCH);

	// XWebServer server;
	// while (true)
	// {
	// 	sleep(1000);
	// }
	
    XMYSQLLINSTANCE()->init("ssh.xinxiao.wang", 26666, "will", "pmjswjk", "XX");

    XConnectionPtr _connectPtr_temp = XMYSQLLINSTANCE()->getConnection();

    _connectPtr_temp->autoCommit(true);

    string _str = "select * from XUserInfoBase;";

    _connectPtr_temp->executeQuery(_str, nullptr, [&] (sql::ResultSet *_res) {
		while (_res->next())
        {
            int id = _res->getInt(1);
            string label = _res->getString(2);
			string phone = _res->getString(3);
			string email = _res->getString(4);

            XLOG_INFO("id, password, phone, email \n%d, %s, %s, %s", id, label.c_str(), phone.c_str(), email.c_str());
        }
	}, nullptr);

	XLOG_INFO("pid = %d", getpid());
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(2007);
	EchoServer server(&loop, listenAddr);
	server.start();
	loop.loop();	

	return 0;
}