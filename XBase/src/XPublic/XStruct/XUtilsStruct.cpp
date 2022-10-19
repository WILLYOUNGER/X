/**
*  @file     XUtilsStruct.h
*  @brief    各工具的数据结构类的实现
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/3
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/3   | 1.0.0.0   | wangxinxiao    | Create file
*-
*/

#include "XUtilsStruct.h"

/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    XJsonValue::XJsonValue()
    {
        m_XJsonType_type = XJSONTYPE_NONE;
    }

    XJsonValue::XJsonValue(long value) : m_l_value(value)
    {
        m_XJsonType_type = XJSONTYPE_LONG;
    }

    XJsonValue::XJsonValue(bool value) : m_b_value(value)
    {
        m_XJsonType_type = XJSONTYPE_BOOL;
    }

    XJsonValue::XJsonValue(std::string value) : m_str_value(value)
    {
        m_XJsonType_type = XJSONTYPE_STRING;
    }

    XJsonValue::XJsonValue(double value) : m_d_value(value)
    {
        m_XJsonType_type = XJSONTYPE_DOUBLE;
    }

    XJsonValue::XJsonValue(XJsonPtr value) : m_xJsonPtr_value(value)
    {
        m_XJsonType_type = XJSONTYPE_OBJECT;
    }

    XJsonValue::XJsonValue(std::list<XJsonValuePtr> value) : m_listXJsonPtr_value(value)
    {
        m_XJsonType_type = XJSONTYPE_ARRAY;
    }

    void XJsonValue::setLongValue(long value)
    {
        m_XJsonType_type = XJSONTYPE_LONG;
        m_l_value = value;
    }

    void XJsonValue::setDoubleValue(double value)
    {
        m_XJsonType_type = XJSONTYPE_DOUBLE;
        m_d_value = value;
    }

    void XJsonValue::setStringValue(std::string value)
    {
        m_XJsonType_type = XJSONTYPE_STRING;
        m_str_value = value;
    }

    void XJsonValue::setBoolValue(bool value)
    {
        m_XJsonType_type = XJSONTYPE_BOOL;
        m_b_value = value;
    }

    void XJsonValue::setArrayValue(std::list<XJsonValuePtr> value)
    {
        m_XJsonType_type = XJSONTYPE_ARRAY;

        for (auto iter = value.begin(); iter != value.end(); iter++)
        {
            m_listXJsonPtr_value.push_back(*iter);
        }
    }

    void XJsonValue::setObjectValue(XJsonPtr value)
    {
        m_XJsonType_type = XJSONTYPE_OBJECT;

        m_xJsonPtr_value = value;
    }

    XJsonValue::~XJsonValue()
    {

    }

    XJson::XJson()
    {
    }

    XJson::~XJson()
    {

    }

    int XJson::setKeyValue(std::string key, XJsonValuePtr value)
    {
        if (nullptr == value)
        {
            return 1;
        }
        m_mapStrXJVPtr_content[key] = value;
        return 0;
    }

    void XJson::getAllKeyValue(std::map<std::string, XJsonValuePtr> &allKeyValue)
    {
        for (auto iter = m_mapStrXJVPtr_content.begin(); iter != m_mapStrXJVPtr_content.end(); iter++)
        {
            allKeyValue[iter->first] = iter->second;
        }
    }

    void XJson::clear()
    {
        m_mapStrXJVPtr_content.clear();
    }

    void XJson::deleteKey(std::string key)
    {
        m_mapStrXJVPtr_content.erase(key);
    }
};
