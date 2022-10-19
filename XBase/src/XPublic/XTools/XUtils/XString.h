/**
*  @file     XString.h
*  @brief    字符串工具库
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/9/21
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/9/21 | 1.0.0.0  | wangxinxiao      | Create file
*-
*/

#ifndef X_PUBLIC_TOOLS_UTILS_STRING_H
#define X_PUBLIC_TOOLS_UTILS_STRING_H

#include <string>

namespace XSTRINGTOOL {

/**
* @brief 拼接字符串,最长不超过1024
* @param 
* @return string
*/
std::string PUB_strformat(const char *format, ...);
//{
//    va_list valst;
//    va_start(valst, format);
//
//    char _c_buffer_ptr[1024] = {0};
//
//    int m = vsnprintf(_c_buffer_ptr, 1023, format, valst);
//    va_end(valst);
//
//    return std::string(_c_buffer_ptr);
//}

}



#endif /* X_PUBLIC_TOOLS_UTILS_STRING_H */
