/**
*  @file XTestServlet.h
*  @brief    博客servlet类
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/6
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/6 | 1.0.0.0  | wangxinxiao      | Create file
*-
*/

#ifndef X_TEST_BLOGSERVLET_H
#define X_TEST_BLOGSERVLET_H

#include "XServlet.h"
#include "XServletDefine.h"

/**
 * @brief 测试servlet类
 * 
 */
class XBlogServlet : public XServlet
{
public:
	XBlogServlet()
	{
		setPath("/getAllBlog");
	}

	virtual void doGet(XNETSTRUCT::XRequest &req, XNETSTRUCT::XResponse &res) override;
};

REGISETRSERVLET(XBlogServlet)

#endif /* X_TEST_BLOGSERVLET_H */