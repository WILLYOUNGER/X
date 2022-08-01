#include "XBaseNet.h"
#include "XWebServer.h"
#include "XLog/XLog.h"
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

//#include <Config.h>
using namespace std;
using namespace XNETBASE;
using namespace rapidjson;
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

	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	Document d;
	d.Parse(json);

	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	cout << buffer.GetString() << endl;

	return 0;
}