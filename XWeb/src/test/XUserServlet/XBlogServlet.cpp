#include "XBlogServlet.h"

#include <iostream>
#include <sys/mman.h>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <iomanip>

#include "XHttpStruct.h"
#include "XFile.h"

using namespace XNETSTRUCT;
using namespace XFILETOOL;
using namespace std;

static int split(std::string &str, char _sig, std::string &res)
{
	int pos = 0;
	while (str.length() > 0 && str[pos] == _sig)
	{
		pos++;
	}
	str = str.substr(pos, str.length() - pos);
	pos = str.find(_sig);
	if (pos == -1)
	{
		res = str.substr(0, str.length());
		str = "";
		return 0;
	}
	else
	{
		res = str.substr(0, pos);
		str = str.substr(pos + 1, str.length() - pos);
		return 1;
	}
}

void XBlogServlet::doGet(XRequest &req, XResponse &res)
{
	if (XFILETOOLINSTANCE()->dirOrFileExist(".\\blog"))
	{
		std::vector<std::string> _vecStr_fileName;
		std::vector<std::string> _vecStr_suffix;
		_vecStr_suffix.push_back("md");

		XFILETOOLINSTANCE()->dirFileNames("./blog", _vecStr_suffix, _vecStr_fileName);

		XJsonPtr _xJsonPtr_res = make_shared<XJson>();
		XJsonValuePtr _XJVP_res = make_shared<XJsonValue>();
		std::list<XJsonValuePtr> _listXJVP_items;
		for (int i = 0; i < _vecStr_fileName.size(); i++)
		{
			XJsonValuePtr _XJVP_item = make_shared<XJsonValue>();
			XJsonPtr _xJsonPtr_item = make_shared<XJson>();
			//id
			XJsonValuePtr _XJVP_id = make_shared<XJsonValue>();
			_XJVP_id->setIntValue(i+1);
			_xJsonPtr_item->setKeyValue("id", _XJVP_id);
			//title
			XJsonValuePtr _XJVP_title = make_shared<XJsonValue>();
			std::string _str_title;
			std::string _str_allTitle = _vecStr_fileName[i];
			split(_str_allTitle, '.', _str_title);
			_XJVP_title->setStringValue(_str_title);
			_xJsonPtr_item->setKeyValue("title", _XJVP_title);
			_XJVP_item->setObjectValue(_xJsonPtr_item);

			struct stat _file_stat;
			std::string _str_path = "./blog/" + _vecStr_fileName[i];
			stat(_str_path.c_str(), &_file_stat);
			std::stringstream _strStream_time;
			_strStream_time << std::put_time(std::localtime(&(_file_stat.st_mtime)), "%D");

			//time
			XJsonValuePtr _XJVP_time = make_shared<XJsonValue>();
			_XJVP_time->setStringValue(_strStream_time.str());
			_xJsonPtr_item->setKeyValue("time", _XJVP_time);
			_XJVP_item->setObjectValue(_xJsonPtr_item);

			std::ifstream f{_str_path.c_str(), std::ios::binary};
			std::stringstream _strStream_content;
			_strStream_content << f.rdbuf();
			std::string _str_content = _strStream_content.str();

			//content
			XJsonValuePtr _XJVP_content = make_shared<XJsonValue>();
			_XJVP_content->setStringValue(_str_content);
			_xJsonPtr_item->setKeyValue("content", _XJVP_content);
			_XJVP_item->setObjectValue(_xJsonPtr_item);
			_listXJVP_items.push_back(_XJVP_item);
		}
		_XJVP_res->setArrayValue(_listXJVP_items);
		_xJsonPtr_res->setKeyValue("blogs", _XJVP_res);
		res.setNotEmpty();
		res.setHttpCode(JSON_RESPONSE);

		std::string json;

		if (0 == XJSONTOOLINSTANCE()->jsonToString(_xJsonPtr_res, json))
		{
			res.setContent(json);
		}
		else
		{
			XLOG_ERROR("json to string error!");
		}
	}
	else
	{
		XLOG_ERROR("%s", "dir is not exist!")
	}
}