/**
*  @file     XFile.h
*  @brief    文件工具库
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/7
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/1   | 1.0.0.0   | wangxinxiao    | Create file(add XJsonTool)
*  2022/8/7   | 1.0.1.0   | wangxinxiao    | add XFileTool
*-
*/

#ifndef X_PUBLIC_TOOLS_UTILS_FIEL_H
#define X_PUBLIC_TOOLS_UTILS_FILE_H

#include <vector>
#include <list>

#include "rapidjson/document.h"
#include "XUtilsStruct.h"

/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    class XJsonTool
    {
    public:
        static XJsonTool* GetInstance();
        XJsonTool();
        ~XJsonTool();

        bool init();

        /**
         * @brief 读取并解析json到单例中
         * 
         * @param json 传入的json字符串
         * @param xjson 解析后的json值
         * @return int
         *  <em> 0 <em> 正确
         *  <em> 1 <em> 解析json字符串失败
         *  <em> 2 <em> json字符串为空
         *  <em> 3 <em> json字符串解析后不是json Object
         *  <em> 4 <em> json字符串中存在key的值不为String
         */
        int openJsonByString(std::string json, XJsonPtr xjson);

        /**
         * @brief 读取并解析文件中的json
         * 
         * @param jsonfileName 
         * @param XJsonPtr 解析后的json内容
         * @return int 
         *  <em> 0 <em> 正确
         *  <em> 1 <em> 文件不存在
         *  <em> 2 <em> 解析失败
         */
        int openJsonByFile(std::string jsonfileName, XJsonPtr xjson);

        /**
         * @brief 将json类解析为字符串
         * 
         * @param xjson json类
         * @param str json字符串
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 5 <em> xjson为空
         */
        int jsonToString(XJsonPtr xjson, std::string &str);
        
        /**
         * @brief 将json字符串保存入文件中
         * 
         * @param json 
         * @return true 
         * @return false 
         */
        bool saveFileByString(std::string fileName, std::string json);

        /**
         * @brief 将json类保存入文件中
         * 
         * @param fileName 
         * @param xjson 
         * @return true 
         * @return false 
         */
        bool saveFileByJson(std::string fileName, XJsonPtr xjson);
    private:
        /**
         * @brief 解析json到XJson中
         * 
         * @param json 
         * @param xjson 
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 4 <em> json字符串中存在key的值不为String
         */
        int buildXJson(rapidjson::Value &json, XJsonPtr xjson);

        /**
         * @brief 解析json列表到list
         * 
         * @param json 需要解析的json
         * @param list 
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 4 <em> json字符串中存在key的值不为String
         */
        int parseList(rapidjson::Value &json, std::list<XJsonValuePtr> &list);

        /**
         * @brief 将xjson类解析为rapidjson
         * 
         * @param json 
         * @param xjson 
         * @param doc 根
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 5 <em> xjson为空 
         */
        int xJsonToRapidJson(rapidjson::Value &json, XJsonPtr xjson, rapidjson::Document &doc);

        /**
         * @brief 将xjson类解析为rapidjsonArray
         * 
         * @param json 
         * @param xjsonValue 
         * @param doc 
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 5 <em> xjson为空 
         */
        int xJsonToRapidJsonArray(rapidjson::Value &json, XJsonValuePtr xjsonValue, rapidjson::Document &doc);
    private:
        /**
         * @brief 返回值枚举
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 解析json字符串失败
         *  <em> 2 <em> json字符串为空
         *  <em> 3 <em> json字符串解析后不是json Object
         *  <em> 4 <em> json字符串中存在key的值不为String
         */
        enum jsonToolReturn
        {
            JSONTOOLRETURN_NORMAL = 0,
            JSONTOOLRETURN_PARSEERROR = 1,
            JSONTOOLRETURN_JSONSTRINGNULL = 2,
            JSONTOOLRETURN_JSONSTRINGISNOTJSONOBJECT = 3,
            JSONTOOLRETURN_JSONSTRINGKEYISNOTSTRING = 4,
            JSONTOOLRETURN_JSONOBJECTISNULL = 5
        };

        static XJsonTool* m_xJsonTool_instance;
    };

    class XFileTool
    {
    public:
        static XFileTool* GetInstance();

        XFileTool();

        ~XFileTool();

        void init();

        //目录或文件是否存在
        bool dirOrFileExist(std::string dirOrFileName);

        /**
         * @brief 判断是目录还是文件
         * 
         * @param dirOrFileName 名称
         * @return int 
         *  <em> 0 <em> 不存在
         *  <em> 1 <em> 是目录
         *  <em> 2 <em> 是文件
         */
        int fileOrDir(std::string dirOrFileName);

        /**
         * @brief 目录中文件的数量
         * 
         * @param dirName 目录名称
         * @param number 文件数量（包括隐藏文件）
         * @param isNeedChildDir 是否包含子文件夹
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 目录不存在
         *  <em> 2 <em> 不是目录
         *  <em> 3 <em> 不是目录也不是文件
         *  <em> 4 <em> 是文件
         */
        int dirFileNumber(std::string dirName, int &number, bool isNeedChildDir);

        /**
         * @brief 目录中文件名称
         * 
         * @param dirName 目录名称
         * @param suffix 需要的后缀名的名称数组
         * @param fileNames 返回的文件名称
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 目录不存在
         */
        int dirFileNames(std::string dirName, std::vector<std::string> &suffix, std::vector<std::string> &fileNames);

    private:
        static XFileTool* m_xFileTool_instance;
    };

    #define XJSONTOOLINSTANCE() XJsonTool::GetInstance()
    #define XFILETOOLINSTANCE() XFileTool::GetInstance()
};

#endif //X_PUBLIC_TOOLS_UTILS_FILE_H