/**
*  @file     XUtilsStruct.h
*  @brief    各工具的数据结构类的定义
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

#ifndef X_PUBLIC_STRUCT_UTILSSTRUCT_H
#define X_PUBLIC_STRUCT_UTILSSTRUCT_H

#include <map>
#include <list>
#include <memory>
#include <string>

/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    class XJson;
    class XJsonValue;

    typedef std::shared_ptr<XJson> XJsonPtr;
    typedef std::shared_ptr<XJsonValue> XJsonValuePtr;

    typedef enum _xjson_type_
    {
        XJSONTYPE_NONE = 0,
        XJSONTYPE_LONG,
        XJSONTYPE_DOUBLE,
        XJSONTYPE_STRING,
        XJSONTYPE_BOOL,
        XJSONTYPE_OBJECT,
        XJSONTYPE_ARRAY,
    } XJSONTYPE;

    class XJsonValue
    {
    public:
        XJsonValue();
        XJsonValue(long value);
        XJsonValue(bool value);
        XJsonValue(std::string value);
        XJsonValue(double value);
        XJsonValue(XJsonPtr value);
        XJsonValue(std::list<XJsonValuePtr> value);

        ~XJsonValue();

        void setLongValue(long value);
        void setDoubleValue(double value);
        void setStringValue(std::string value);
        void setBoolValue(bool value);
        void setArrayValue(std::list<XJsonValuePtr> value);
        void setObjectValue(XJsonPtr value);

        inline XJSONTYPE getType()
        {
            return m_XJsonType_type;
        }

        inline long getLongValue()
        {
            return m_l_value;
        }

        inline double getDoubleValue()
        {
            return m_d_value;
        }

        inline bool getBoolValue()
        {
            return m_b_value;
        }

        inline std::string getStringValue()
        {
            return m_str_value;
        }

        inline void getArrayValue(std::list<XJsonValuePtr> &res)
        {
            res.clear();
            for (auto iter = m_listXJsonPtr_value.begin(); iter != m_listXJsonPtr_value.end(); iter++)
            {
                res.push_back((*iter));
            }
        }

        inline XJsonPtr getObjectValue()
        {
            return m_xJsonPtr_value;
        }
    private:
        XJSONTYPE m_XJsonType_type { XJSONTYPE_NONE };

        long m_l_value { 0 };
        XJsonPtr m_xJsonPtr_value;
        double m_d_value { 0 };
        std::string m_str_value { "" };
        bool m_b_value { false };
        std::list<XJsonValuePtr> m_listXJsonPtr_value;
    };

    class XJson
    {
    public:
        XJson();
        ~XJson();
        
        /**
         * @brief 设置键值对
         * 
         * @param key 
         * @param value 
         * @return int 
         * <em> 0 <em> 正常
         * <em> 1 <em> value为空
         */
        int setKeyValue(std::string key, XJsonValuePtr value);

        inline XJsonValuePtr getValue(std::string key)
        {
            if (m_mapStrXJVPtr_content.count(key) == 1)
            {
                return m_mapStrXJVPtr_content[key];
            }
            else
            {
                return std::make_shared<XJsonValue>();
            }
        }

        void getAllKeyValue(std::map<std::string, XJsonValuePtr> &allKeyValue);

        void clear();

        void deleteKey(std::string key);
    private:
        std::map<std::string, XJsonValuePtr> m_mapStrXJVPtr_content;
    };
};

#endif //X_PUBLIC_STRUCT_UTILSSTRUCT_H
