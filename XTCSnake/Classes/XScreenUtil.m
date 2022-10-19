//
//  XScreenUtil.m
//  XTCSnake
//
//  Created by Will Young on 2022/10/11.
//

#import <Foundation/Foundation.h>
#import "XScreenUtil.h"
 
@implementation NotchScreenUtil
 
+ (BOOL)isIPhoneNotchScreen{
    BOOL result = NO;
    if (UIDevice.currentDevice.userInterfaceIdiom != UIUserInterfaceIdiomPhone) {
        return result;
    }
    if (@available(iOS 11.0, *)) {
        CGSize size = [UIScreen mainScreen].bounds.size;
        NSInteger notchValue = size.width / size.height * 100;
        UIWindow *mainWindow = [[[UIApplication sharedApplication] delegate] window];
        if (mainWindow.safeAreaInsets.bottom > 0.0 || notchValue == 216 || notchValue == 46) {
            result = YES;
        }
    }
    return result;
}
 
+ (CGFloat)getIPhoneNotchScreenHeight{
    /*
     * iPhone8 Plus  UIEdgeInsets: {20, 0, 0, 0}
     * iPhone8       UIEdgeInsets: {20, 0, 0, 0}
     * iPhone XR     UIEdgeInsets: {44, 0, 34, 0}
     * iPhone XS     UIEdgeInsets: {44, 0, 34, 0}
     * iPhone XS Max UIEdgeInsets: {44, 0, 34, 0}
     */
    CGFloat bottomSpace = 0;
    UIEdgeInsets safeAreaInsets = UIEdgeInsetsMake(0, 0, 0, 0);
    if (@available(iOS 11.0, *)) {
        if (@available(iOS 13.0, *)) {
            safeAreaInsets = [UIApplication sharedApplication].windows.firstObject.safeAreaInsets;
        } else {
            safeAreaInsets = [[UIApplication sharedApplication] delegate].window.safeAreaInsets;
        }
        switch (UIApplication.sharedApplication.statusBarOrientation) {
            case UIInterfaceOrientationPortrait:
            {
                bottomSpace = safeAreaInsets.bottom;
            }
                break;
            case UIInterfaceOrientationLandscapeLeft:
            {
                bottomSpace = safeAreaInsets.right;
            }
                break;
            case UIInterfaceOrientationLandscapeRight:
            {
                bottomSpace = safeAreaInsets.left;
            }
                break;
            case UIInterfaceOrientationPortraitUpsideDown:
            {
                bottomSpace = safeAreaInsets.top;
            }
                break;
            default:
            {
                bottomSpace = safeAreaInsets.bottom;
            }
                break;
        }
    }
    return bottomSpace;
}
 
@end
