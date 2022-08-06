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
*  2022/8/1   | 1.0.0.0   | wangxinxiao    | Create file
*-
*/

#include "XFile.h"

#include <map>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "XLog.h"

using namespace std;
/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    XJsonTool* XJsonTool::m_xJsonTool_instance = nullptr; 

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
};