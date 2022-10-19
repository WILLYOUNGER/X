#include "XTime.h"

#include "iostream"
#include <chrono>
#include <ctime>
#include <string>

#include "time.h"

namespace XTIMETOOL {

static unsigned int g_i_time = (unsigned int)time(0);

int PUB_getRandInt(int begin, int end)
{
    if (time(0) != g_i_time)
    {
        g_i_time = (unsigned int)time(0);
        srand((unsigned int)g_i_time);
    }
    int _i_res = begin + rand() % (end - begin + 1);
    
    return _i_res;
}


float PUB_getRandFloat(float begin, float end)
{
    if (time(0) != g_i_time)
    {
        srand((unsigned int)time(0));
    }
    float _f_res = begin + (float)(rand()) / RAND_MAX * (end - begin);
    
    return _f_res;
}


float PUB_adjustmentRange(float adjustmentNum, float begin, float end)
{
    if (adjustmentNum > end)
    {
        adjustmentNum = end;
    }
    else if (adjustmentNum < begin)
    {
        adjustmentNum = begin;
    }
    return adjustmentNum;
}

void PUB_getNowTime(long &s, long &ms)
{
    std::chrono::system_clock::time_point time_point_now = std::chrono::system_clock::now(); // 获取当前时间点
    std::chrono::system_clock::duration duration_since_epoch
            = time_point_now.time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
    time_t microseconds_since_epoch
            = duration_cast<std::chrono::microseconds>(duration_since_epoch).count(); // 将时长转换为微秒数
    time_t seconds_since_epoch = microseconds_since_epoch / 1000000; // 将时长转换为秒数
    std::tm current_time = *std::localtime(&seconds_since_epoch); // 获取当前时间（精确到秒）
    time_t tm_microsec = microseconds_since_epoch % 1000; // 当前时间的微妙数
    time_t tm_millisec = microseconds_since_epoch / 1000 % 1000; // 当前时间的毫秒数
    
    s = seconds_since_epoch;
    ms = microseconds_since_epoch;
}

void PUB_log(std::string log)
{
    long _l_sec, _l_microsec;
    PUB_getNowTime(_l_sec, _l_microsec);
    std::cout << log << " sec: " << _l_sec << " microsec: " << _l_microsec << std::endl;
}

std::string PUB_second2String(long time)
{
    tm *tm_ = std::localtime(&time);                // 将time_t格式转换为tm结构体
    int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
    year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
    month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
    day = tm_->tm_mday;                        // 临时变量，日。
    hour = tm_->tm_hour;                       // 临时变量，时。
    minute = tm_->tm_min;                      // 临时变量，分。
    second = tm_->tm_sec;                      // 临时变量，秒。
    char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
    sprintf(yearStr, "%d", year);              // 年。
    sprintf(monthStr, "%d", month);            // 月。
    sprintf(dayStr, "%d", day);                // 日。
    sprintf(hourStr, "%d", hour);              // 时。
    sprintf(minuteStr, "%d", minute);          // 分。
    if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
    {
        minuteStr[2] = '\0';
        minuteStr[1] = minuteStr[0];
        minuteStr[0] = '0';
    }
    sprintf(secondStr, "%d", second);          // 秒。
    if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
    {
        secondStr[2] = '\0';
        secondStr[1] = secondStr[0];
        secondStr[0] = '0';
    }
    char s[20];                                // 定义总日期时间char*变量。
    sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
    std::string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
    return str;                                // 返回转换日期时间后的string变量。
}
}
