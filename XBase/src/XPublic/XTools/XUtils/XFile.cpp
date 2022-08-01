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

using namespace std;
/**
 * @brief 文件类工具命名空间，除了文件的读取写入外，还负责生成xml json  protobuff等传输协议
 * 
 */
namespace XFILETOOL
{
    XJsonTool::XJsonTool()
    {

    }

    XJsonTool::~XJsonTool()
    {

    }

    XJsonTool* XJsonTool::GetInstance()
    {
        return nullptr;
    }

    bool XJsonTool::beginCreate()
    {
        return false;
    }

    string XJsonTool::endCreate()
    {
        return "";
    }

    bool XJsonTool::init()
    {
        return false;
    }

    bool XJsonTool::setKeyInt(string key, int value)
    {
        return false;
    }

    bool XJsonTool::setKeyBool(string key, bool value)
    {
        return false;
    }

    bool XJsonTool::setKeyString(string key, string value)
    {
        return false;
    }
};