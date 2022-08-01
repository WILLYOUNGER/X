/**
*  @file wheel_timer.h
*  @brief    时间轮
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/7/9
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/5/2 | 1.0.0.0  | wangxinxiao      | Create file
*  2022/7/9 | 1.0.1.0  | wangxinxiao      | add TimerNodeInfoBase
*-
*/

#ifndef X_PUBLIC_TOOLS_UTILS_WHEELTIMER_H
#define X_PUBLIC_TOOLS_UTILS_WHEELTIMER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>

/**
 * @brief 通用工具类命名空间，主要是网络类，时间类和数字类工具
 */
namespace XUTILSTOOL{

class XWheelTimer;

class TimerNodeInfoBase
{
public:
    virtual bool operator==(TimerNodeInfoBase &_second)
    {
        return false;
    }
};

class XTimerNode
{
public:
    XTimerNode(int rot, int st, TimerNodeInfoBase _client, std::function<void(TimerNodeInfoBase)> _func):rotation(rot), slot_time(st), client(_client), prev(nullptr), next(nullptr), _cb_func(_func) {}
public:
    int rotation;
    int slot_time;
    std::function<void(TimerNodeInfoBase)> _cb_func;
    TimerNodeInfoBase client;
    XTimerNode* prev;
    XTimerNode* next;
};

class XWheelTimer
{
public:
    XWheelTimer();
    ~XWheelTimer();
    void addTimer(int time, TimerNodeInfoBase _client, std::function<void(TimerNodeInfoBase)> _cb_func);
    void deleteTimer(struct TimerNodeInfoBase _clinet);
    void adjustTimer(int time, struct TimerNodeInfoBase _client);
    void tick();
private:
    int m_curSlot;
    static const int N = 60;
    static const int SI = 1;
    XTimerNode* m_slots[N];
};

}
#endif /* X_PUBLIC_TOOLS_UTILS_WHEELTIMER_H */
