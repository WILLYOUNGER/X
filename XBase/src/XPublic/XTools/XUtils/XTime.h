/**
*  @file     XMath.h
*  @brief    数学公式库
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/6/4
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/6/4 | 1.0.0.0  | wangxinxiao      | Create file
*-
*/

#ifndef X_PUBLIC_TOOLS_UTILS_TIME_H
#define X_PUBLIC_TOOLS_UTILS_TIME_H

#include "string"

namespace XTIMETOOL {

/**
* @brief 获取随机整数
* @param begin：前范围（包括begin）后范围（包括end）
* @return int 随机整数
*/
int PUB_getRandInt(int begin, int end);

/**
* @brief 获取随机有理数
* @param begin：前范围（包括begin）后范围（包括end）
* @return float 随机有理数
*/
float PUB_getRandFloat(float begin, float end);

/**
* @brief 调整范围，限定数的最大最小
* @param begin：前范围（包括begin）后范围（包括end）
* @return 调整后的数
*/
float PUB_adjustmentRange(float adjustmentNum, float begin, float end);

/**
* @brief 获取当前时间
* @param s：秒  ms：毫秒
*/
void PUB_getNowTime(long &s, long &ms);

/**
 * @brief  当前秒数
 * @return 对应 文本 "%s-%s-%s %s:%s:%s"
 */
std::string PUB_second2String(long s);

/**
* @brief 打印日志
* @param log:日志
*/
void PUB_log(std::string log);

}

#endif /* X_PUBLIC_TOOLS_UTILS_TIME_H */
