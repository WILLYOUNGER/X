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

    std::string XJsonTool::jsonToString(XJsonPtr xjson)
    {
        
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
};