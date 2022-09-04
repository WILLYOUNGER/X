#include "XWheelTimer.h"

namespace XUTILSTOOL
{
    XWheelTimer::XWheelTimer()
    {
        m_curSlot = 0;
        for(int i = 0; i < N; i++)
        {
            m_slots[i] = nullptr;
        }
    }

    XWheelTimer::~XWheelTimer()
    {
        for (int i = 0; i < N; i++)
        {
            if (m_slots[i] != nullptr)
            {
                XTimerNode *temp = m_slots[i];
                while(temp)
                {
                    m_slots[i] = temp->next;
                    delete temp;
                    temp = m_slots[i];
                }
            }
        }
    }

    void XWheelTimer::addTimer(int time, TimerNodeInfoBase _client, std::function<void(TimerNodeInfoBase)> _cb_func)
    {
        if (time < 0)
        {
            return;
        }
        int tick = 0;
        if (time < 1)
        {
            tick = 1;
        }
        else
        {
            tick = time / SI;
        }
        int ro = tick / N;
        int st = (m_curSlot + (tick % N)) % N;
        XTimerNode *_time = new XTimerNode(ro, st, _client, _cb_func);
        if (m_slots[st] == nullptr)
        {
            m_slots[st] = _time;
        }
        else
        {
            _time->next = m_slots[st];
            m_slots[st]->prev = _time;
            m_slots[st] = _time;
        }
    }

    void XWheelTimer::adjustTimer(int time, struct TimerNodeInfoBase _client)
    {
        if (time < 0)
        {
            return;
        }
        for (int i = 0; i < N; i ++)
        {
            XTimerNode *temp = m_slots[i];
            while (temp)
            {
                if (temp->client ==_client)
                {
                    int tick = 0;
                    if (time < 1)
                    {
                        tick = 1;
                    }
                    else
                    {
                        tick = time / SI;
                    }
                    int ro = tick / N;
                    int sl = (m_curSlot + (tick % N)) % N;
                    temp->rotation = ro;
                    temp->slot_time = sl;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
    }

    void XWheelTimer::deleteTimer(struct TimerNodeInfoBase _client)
    {
        for (int i = 0; i < N; i++)
        {
            XTimerNode *temp = m_slots[i];
            while (temp)
            {
                if (temp->client == _client)
                {
                    if (temp == m_slots[i])
                    {
                        if (temp->next)
                        {
                            temp->next->prev = nullptr;
                            m_slots[i] = temp->next;
                            delete temp;
                            return;
                        }
                        delete temp;
                        m_slots[i] = nullptr;
                        return;
                    }
                    else
                    {
                        if (temp->next)
                        {
                            temp->next->prev = temp->prev;
                            temp->prev->next = temp->next;
                            delete temp;
                            return;
                        }
                        else
                        {
                            temp->prev->next = nullptr;
                            delete temp;
                            return;
                        }
                    }
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
    }

    void XWheelTimer::tick()
    {
        XTimerNode* node = m_slots[m_curSlot];
        while (node)
        {
            if (node->rotation > 0)
            {
                node->rotation--;
                node = node->next;
            }
            else
            {
                node->_cb_func(node->client);
                if (node == m_slots[m_curSlot])
                {
                    m_slots[m_curSlot] = node->next;
                    if (m_slots[m_curSlot])
                    {
                        m_slots[m_curSlot]->prev = nullptr;
                    }
                    delete node;
                    node = m_slots[m_curSlot];
                }
                else
                {
                    node->prev->next = node->next;
                    if (node->next)
                    {
                        node->next->prev = node->prev;
                    }
                    XTimerNode* temp = node->next;
                    delete node;
                    node = temp;
                }
            }
        }
        m_curSlot = m_curSlot+1;
        m_curSlot = m_curSlot % N;
    }
};
