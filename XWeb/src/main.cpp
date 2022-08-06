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

	// const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
	// Document d;
	// d.Parse(json);

	// Value& s = d["stars"];
	// s.SetInt(s.GetInt() + 1);
	
	// Value contact;
	// contact.SetObject();
	// contact.AddMember("name", "Milo", d.GetAllocator());
	// contact.AddMember("married", true, d.GetAllocator());

	// d.AddMember("project", contact, d.GetAllocator());

	// Value array;
	// array.SetArray();
	// array.PushBack(true, d.GetAllocator());
	// array.PushBack("true", d.GetAllocator());

	// d.AddMember("array", array, d.GetAllocator());

	// StringBuffer buffer;
	// Writer<StringBuffer> writer(buffer);
	// d.Accept(writer);

	// cout << buffer.GetString() << endl;

	const char* json = "{\"project\":\"rapidjson\",\"stars\":11,\"object\":{\"name\":\"Milo\",\"married\":null},\"array\":[true, 123]}";
	
	XJsonPtr _xJsonPtr_json = make_shared<XJson>();

	XJSONTOOLINSTANCE()->openJsonByString(string(json), _xJsonPtr_json);

	string _str_json;
	int _i_return = XJSONTOOLINSTANCE()->jsonToString(_xJsonPtr_json, _str_json);
	if (0 == _i_return)
	{
		cout << _str_json << endl;
	}
	else
	{
		cout << _i_return << endl;
	}
	

	return 0;
}