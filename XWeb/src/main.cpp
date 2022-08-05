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

	const char* json = "{\"project\":\"rapidjson\",\"stars\":11,\"oject\":{\"name\":\"Milo\",\"married\":true},\"array\":[true,\"true\"]}";
	
	XJsonPtr _xJsonPtr_json = make_shared<XJson>();

	XJsonTool::GetInstance()->openJsonByString(string(json), _xJsonPtr_json);

	cout << _xJsonPtr_json->getValue("project")->getStringValue() << endl 
		 << _xJsonPtr_json->getValue("stars")->getIntValue() << endl
		 << _xJsonPtr_json->getValue("oject")->getObjectValue()->getValue("name")->getStringValue() << endl
		 << _xJsonPtr_json->getValue("oject")->getObjectValue()->getValue("married")->getBoolValue() << endl
		 << _xJsonPtr_json->getValue("array")->getArrayValue().front()->getBoolValue() << endl
		 << _xJsonPtr_json->getValue("array")->getArrayValue().back()->getStringValue() << endl;

	return 0;
}