/**
*  @file     XFile.cpp
*  @brief    文件工具库的实现
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/1
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/1   | 1.0.0.0   | wangxinxiao    | Create file(add XJsonTool)
*  2022/8/7   | 1.0.1.0   | wangxinxiao    | add XFileTool
*-
*/

#include "XFile.h"

#include <map>
#include <vector>
#include <regex>    //正则表达式
#include <unistd.h> //判断文件权限
#include <filesystem>   //文件夹中文件数量
#include <dirent.h> //文件夹中文件名依赖

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "XLog.h"

using namespace std;
using namespace std::filesystem;
/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    XJsonTool* XJsonTool::m_xJsonTool_instance = nullptr; 
    XFileTool* XFileTool::m_xFileTool_instance = nullptr;

    XJsonTool::XJsonTool()
    {

    }

    XJsonTool::~XJsonTool()
    {

    }

    XJsonTool* XJsonTool::GetInstance()
    {
        if (m_xJsonTool_instance != nullptr)
        {
            m_xJsonTool_instance = new XJsonTool();
            m_xJsonTool_instance->init();
        }
        return m_xJsonTool_instance;
    }

    bool XJsonTool::init()
    {
        return true;
    }

    int XJsonTool::openJsonByString(std::string json, XJsonPtr xjson)
    {
        if (json == "")
        {
            return JSONTOOLRETURN_JSONSTRINGNULL;
        }

        rapidjson::Document doc;
	    doc.Parse(json.c_str());
        if (doc.HasParseError())
        {
            return JSONTOOLRETURN_PARSEERROR;
        }
        if (!doc.IsObject())
        {
            return JSONTOOLRETURN_JSONSTRINGISNOTJSONOBJECT;
        }
        
        xjson->clear();

        return buildXJson(doc, xjson);
    }

    int XJsonTool::openJsonByFile(std::string jsonfileName, XJsonPtr xjson)
    {

    }

    int XJsonTool::jsonToString(XJsonPtr xjson, std::string &str)
    {
        rapidjson::Document json;
        
        if (JSONTOOLRETURN_JSONOBJECTISNULL == xJsonToRapidJson(json, xjson, json))
        {
            return JSONTOOLRETURN_JSONOBJECTISNULL;
        }
        
        rapidjson::StringBuffer buffer;
	    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	    json.Accept(writer);
        str = buffer.GetString();

        return JSONTOOLRETURN_NORMAL;
    }

    bool XJsonTool::saveFileByString(std::string fileName, std::string json)
    {

    }

    bool XJsonTool::saveFileByJson(std::string fileName, XJsonPtr xjson)
    {
        
    }

    int XJsonTool::buildXJson(rapidjson::Value &json, XJsonPtr xjson)
    {
        for (auto jsonIter = json.MemberBegin(); jsonIter != json.MemberEnd(); jsonIter++)
        {
            if (jsonIter->name.IsString())
            {
                XJsonValuePtr _xJVP_value = make_shared<XJsonValue>();
                if (jsonIter->value.IsBool())
                {
                    _xJVP_value->setBoolValue(jsonIter->value.GetBool());
                }
                else if (jsonIter->value.IsString())
                {
                    _xJVP_value->setStringValue(jsonIter->value.GetString());
                }
                else if (jsonIter->value.IsInt())
                {
                    _xJVP_value->setIntValue(jsonIter->value.GetInt());
                }
                else if (jsonIter->value.IsDouble())
                {
                    _xJVP_value->setDoubleValue(jsonIter->value.GetDouble());
                }
                else if (jsonIter->value.IsObject())
                {
                    XJsonPtr _xjsonPtr_temp = make_shared<XJson>();
                    if (JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING == buildXJson(jsonIter->value, _xjsonPtr_temp))
                    {
                        return JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING;
                    }
                    _xJVP_value->setObjectValue(_xjsonPtr_temp);
                }
                else if (jsonIter->value.IsArray())
                {
                    std::list<XJsonValuePtr> _listXJVP_temp;
                    if (JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING == parseList(jsonIter->value, _listXJVP_temp))
                    {
                        return JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING;
                    }
                    _xJVP_value->setArrayValue(_listXJVP_temp);
                }
                xjson->setKeyValue(jsonIter->name.GetString(), _xJVP_value);   
            }
            else
            {
                return JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING;
            }
        }
        return JSONTOOLRETURN_NORMAL;
    }

    int XJsonTool::parseList(rapidjson::Value &json, std::list<XJsonValuePtr> &list)
    {
        for (int i = 0; i < json.Size(); i++)
        {
            XJsonValuePtr _xJVP_value = make_shared<XJsonValue>();
            if (json[i].IsBool())
            {
                _xJVP_value->setBoolValue(json[i].GetBool());
            }
            else if (json[i].IsString())
            {
                _xJVP_value->setStringValue(json[i].GetString());
            }
            else if (json[i].IsInt())
            {
                _xJVP_value->setIntValue(json[i].GetInt());
            }
            else if (json[i].IsDouble())
            {
                _xJVP_value->setDoubleValue(json[i].GetDouble());
            }
            else if (json[i].IsObject())
            {
                XJsonPtr _xjsonPtr_temp = make_shared<XJson>();
                if (JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING == buildXJson(json[i], _xjsonPtr_temp))
                {
                    return JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING;
                }
                _xJVP_value->setObjectValue(_xjsonPtr_temp);
            }
            else if (json[i].IsArray())
            {
                std::list<XJsonValuePtr> _listXJVP_temp;
                if (JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING == parseList(json[i], _listXJVP_temp))
                {
                    return JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING;
                }
                _xJVP_value->setArrayValue(_listXJVP_temp);
            }
            list.push_back(_xJVP_value);
        }
        return JSONTOOLRETURN_NORMAL;
    }

    int XJsonTool::xJsonToRapidJson(rapidjson::Value &json, XJsonPtr xjson, rapidjson::Document &doc)
    {
        json.SetObject();
        std::map<std::string, XJsonValuePtr> _mapStrXJVP_json;
        xjson->getAllKeyValue(_mapStrXJVP_json);
        if (0 == _mapStrXJVP_json.size())
        {
            return JSONTOOLRETURN_JSONOBJECTISNULL;
        }

        for (auto iter = _mapStrXJVP_json.begin(); iter != _mapStrXJVP_json.end(); iter++)
        {
            XJsonValuePtr _XJVP_temp = iter->second;

            if (XJSONTYPE_INT == _XJVP_temp->getType())
            {
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _XJVP_temp->getIntValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_DOUBLE == _XJVP_temp->getType())
            {
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _XJVP_temp->getDoubleValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_STRING == _XJVP_temp->getType())
            {
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _XJVP_temp->getStringValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_BOOL == _XJVP_temp->getType())
            {
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _XJVP_temp->getBoolValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_OBJECT == _XJVP_temp->getType())
            {
                rapidjson::Value _value;
                if (JSONTOOLRETURN_JSONOBJECTISNULL == xJsonToRapidJson(_value, _XJVP_temp->getObjectValue(), doc))
                {
                    return JSONTOOLRETURN_JSONOBJECTISNULL;
                }
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _value, doc.GetAllocator());
            }
            else if (XJSONTYPE_ARRAY == _XJVP_temp->getType())
            {
                rapidjson::Value _value;
                if (JSONTOOLRETURN_JSONOBJECTISNULL == xJsonToRapidJsonArray(_value, _XJVP_temp, doc))
                {
                    return JSONTOOLRETURN_JSONOBJECTISNULL;
                }
                json.AddMember(rapidjson::StringRef(iter->first.c_str(), iter->first.length()), _value, doc.GetAllocator());
            }
        }
        return JSONTOOLRETURN_NORMAL;
    }

    int XJsonTool::xJsonToRapidJsonArray(rapidjson::Value &json, XJsonValuePtr xjsonValue, rapidjson::Document &doc)
    {
        json.SetArray();
        std::list<XJsonValuePtr> _listXJVP_temp;
        xjsonValue->getArrayValue(_listXJVP_temp);
        for (auto iter = _listXJVP_temp.begin(); iter != _listXJVP_temp.end(); iter++)
        {
            XJsonValuePtr _XJVP_temp = (*iter);
            if (XJSONTYPE_INT == _XJVP_temp->getType())
            {
                json.PushBack(_XJVP_temp->getIntValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_DOUBLE == _XJVP_temp->getType())
            {
                json.PushBack(_XJVP_temp->getDoubleValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_STRING == _XJVP_temp->getType())
            {
                json.PushBack(rapidjson::Value(_XJVP_temp->getStringValue(), doc.GetAllocator()).Move(), doc.GetAllocator());
            }
            else if (XJSONTYPE_BOOL == _XJVP_temp->getType())
            {
                json.PushBack(_XJVP_temp->getBoolValue(), doc.GetAllocator());
            }
            else if (XJSONTYPE_OBJECT == _XJVP_temp->getType())
            {
                rapidjson::Value _value;
                if (JSONTOOLRETURN_JSONOBJECTISNULL == xJsonToRapidJson(_value, _XJVP_temp->getObjectValue(), doc))
                {
                    return JSONTOOLRETURN_JSONOBJECTISNULL;
                }
                json.PushBack(_value, doc.GetAllocator());
            }
            else if (XJSONTYPE_ARRAY == _XJVP_temp->getType())
            {
                json.PushBack(_XJVP_temp->getIntValue(), doc.GetAllocator());
                rapidjson::Value _value;
                if (JSONTOOLRETURN_JSONOBJECTISNULL == xJsonToRapidJsonArray(_value, _XJVP_temp, doc))
                {
                    return JSONTOOLRETURN_JSONOBJECTISNULL;
                }
                json.PushBack(_value, doc.GetAllocator());
            }
        }
        return JSONTOOLRETURN_NORMAL;
    }


    XFileTool* XFileTool::GetInstance()
    {
        if (m_xFileTool_instance != nullptr)
        {
            m_xFileTool_instance = new XFileTool();
            m_xFileTool_instance->init();
        }
        return m_xFileTool_instance;
    }

    XFileTool::XFileTool()
    {

    }

    XFileTool::~XFileTool()
    {

    }

    void XFileTool::init()
    {

    }

    bool XFileTool::dirOrFileExist(std::string dirOrFileName)
    {
        return access(dirOrFileName.c_str(), F_OK);
    }

    int XFileTool::dirFileNumber(std::string dirName, int number)
    {
        // if (!exists(dirName))		// 如果目录不存在
        // {
        //     return 1;
        // }
            
        // path root(dirName);
        // //不是目录
        // if (!is_directory(root)) {
        //     return 2;
        // }

        // //不是目录也不是文件
        // if (!is_directory(root) && is_regular_file(root))
        // {
        //     return 3;
        // }

        // // 如果只是单个文件，返回1
        // if (is_regular_file(root)) {
        //     return 4;
        // }
        // // DFS
        // std::stack<path> st;
        // st.push(root);
        // int files = 0;
        // while (!st.empty()) {
        //     path folder = st.top();
        //     st.pop();
        //     directory_entry entry(folder);	//文件入口
        //     directory_iterator list(entry);	//文件入口容器
        //     for (auto& it : list) {
        //         if (is_regular_file(it)) {	//文件的话，文件数++
        //             ++files;
        //         }
        //         if (is_directory(it)) {	//目录的话，入栈
        //             st.push(it);
        //         }
        //     }
        // }
        // return files;
        return 0;
    }

    int XFileTool::dirFileNames(std::string dirName, vector<std::string> &suffix, vector<std::string> &fileNames)
    {
        DIR *p_dir = opendir(dirName.c_str());
        if (p_dir == nullptr) {
            return -1;
        }
    
        struct dirent* p_file = nullptr;
        while ((p_file = readdir(p_dir)) != nullptr) {
            if (strcmp(p_file->d_name, ".") != 0 && strcmp(p_file->d_name, "..") != 0) {
                std::string cur_file_name(p_file->d_name);
                bool ret = false;
                for (int i = 0; i < suffix.size(); i++)
                {
                    std::regex file_reg((".+\\." + suffix[i]).c_str());
                    ret = std::regex_match(cur_file_name, file_reg);
                    if (ret)
                    {
                        fileNames.push_back(cur_file_name);
                        break;
                    }
                }
            }
        }
    
        closedir(p_dir);
        return 0;
    }
};