//
//  XScreenUtil.h
//  XTCSnake
//
//  Created by Will Young on 2022/10/11.
//

#ifndef X_PUBLIC_TOOLS_UTILS_SCREENUTIL_H
#define X_PUBLIC_TOOLS_UTILS_SCREENUTIL_H

/*
 * iPhone刘海屏工具类
 */
@interface NotchScreenUtil : NSObject
 
// 判断是否是刘海屏
+(BOOL)isIPhoneNotchScreen;
 
// 获取刘海屏高度
+(CGFloat)getIPhoneNotchScreenHeight;
 
@end

#endif /* X_PUBLIC_TOOLS_UTILS_COCOS2DX_H */
