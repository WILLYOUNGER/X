/**
*  @file     XBaseStruct.h
*  @brief    基础数据结构
*  Details. 
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/20
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/20   | 1.0.0.0   | wangxinxiao    | Create file
*-
*/
#ifndef X_PUBLIC_STRUCT_BASESTRUCT_H
#define X_PUBLIC_STRUCT_BASESTRUCT_H

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

#endif