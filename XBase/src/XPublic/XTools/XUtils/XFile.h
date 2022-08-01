/**
*  @file     XFile.h
*  @brief    文件工具库
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

#ifndef X_PUBLIC_TOOLS_UTILS_FIEL_H
#define X_PUBLIC_TOOLS_UTILS_FILE_H

#include <string>

/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{

class XJsonTool
{
public:
    XJsonTool* GetInstance();
    XJsonTool();
    ~XJsonTool();

    bool init();

    /**
     * @brief 开始构建json字符串
     * 
     * @return true 
     * @return false 
     */
    bool beginCreate();

    /**
     * @brief 获取从上一次调用beginCreate后构建的字符串
     * 
     * @return std::string 
     */
    std::string endCreate();

    /**
     * @brief 类型为整形
     * 
     * @param key 
     * @param value 
     * @return true 成功
     * @return false 失败
     */
    bool setKeyInt(std::string key, int value);

    /**
     * @brief  类型为字符串型
     * 
     * @param key 
     * @param value 
     * @return true 
     * @return false 
     */
    bool setKeyString(std::string key, std::string value);
    
    /**
     * @brief 类型为布尔型
     * 
     * @param key 
     * @param value 
     * @return true 
     * @return false 
     */
    bool setKeyBool(std::string key, bool value);
private:
};

#define XJSONTOOLINSTANCE() XJsonTool::GetInstance();

};

#endif //X_PUBLIC_TOOLS_UTILS_FILE_H