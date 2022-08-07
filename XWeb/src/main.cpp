#include "XBaseNet.h"
#include "XWebServer.h"
#include "XLog/XLog.h"
#include <iostream>

#include "XFile.h"

//#include <Config.h>
using namespace std;
using namespace XNETBASE;
using namespace XFILETOOL;
int main(int argc, char* argv[])
{
	if (!XLOG->init("XWebLog.txt", 2))
	{
		return 0;
	}

	//XLOG_INFO("%s, version: %d.%d.%d", argv[0], XWEB_VERSION_MAJOR, XWEB_VERSION_MINOR, XWEB_VERSION_PATCH);

	XWebServer server;
	while (true)
	{
		sleep(1000);
	}

	return 0;
}