//
//  XCOCOS2DX.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/10/11.
//

#include "XCOCOS2DX.hpp"

#include "XScreenUtil.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <AudioToolbox/AudioToolbox.h>
#endif

namespace XCOCOSTOOL
{

float PUB_GetBangsHegiht()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    float _f_res = 0;
    if ([NotchScreenUtil isIPhoneNotchScreen])
    {
        _f_res = [NotchScreenUtil getIPhoneNotchScreenHeight];
    }
    return _f_res;
#else
    //Android代码
    return 0;
#endif
}

float PUB_GetVirtualKeyboardHeight()
{
    return 0;
}

void PUB_Vibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    //AudioServicesPlaySystemSound(1519);
    
//    if (@available(iOS 10.0, *)){
//        //设置->声音与触感->关闭系统触感反馈开关，将不会震动
//        UIImpactFeedbackGenerator *feedBackGenertor = [[UIImpactFeedbackGenerator alloc]initWithStyle:UIImpactFeedbackStyleLight];
//        [feedBackGenertor prepare];
//        [feedBackGenertor impactOccurred];
//    }else{
        //震动，1519，1520（kSystemSoundID_Vibrate震动时间过长）
        AudioServicesPlaySystemSound(1519);
//    }
#endif
}


void PUB_MidVibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    //AudioServicesPlaySystemSound(1519);
    
//    if (@available(iOS 10.0, *)){
//        //设置->声音与触感->关闭系统触感反馈开关，将不会震动
//        UIImpactFeedbackGenerator *feedBackGenertor = [[UIImpactFeedbackGenerator alloc]initWithStyle:UIImpactFeedbackStyleLight];
//        [feedBackGenertor prepare];
//        [feedBackGenertor impactOccurred];
//    }else{
        //震动，1519，1520（kSystemSoundID_Vibrate震动时间过长）
        AudioServicesPlaySystemSound(1520);
//    }
#endif
}

void PUB_LongVibrate()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

    //AudioServicesPlaySystemSound(1519);
    
//    if (@available(iOS 10.0, *)){
//        //设置->声音与触感->关闭系统触感反馈开关，将不会震动
//        UIImpactFeedbackGenerator *feedBackGenertor = [[UIImpactFeedbackGenerator alloc]initWithStyle:UIImpactFeedbackStyleLight];
//        [feedBackGenertor prepare];
//        [feedBackGenertor impactOccurred];
//    }else{
        //震动，1519，1520（kSystemSoundID_Vibrate震动时间过长）
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
//    }
#endif
}
}
