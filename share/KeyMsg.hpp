#ifndef __KEY_MSG_HPP__
#define __KEY_MSG_HPP__

#include "TimedEvent.hpp"

class KeyMsg
{
public :
        typedef std::function<bool(int32_t, void*)> SendFuncType;
        KeyMsg(SendFuncType func, TimedEvent::GetTimestampFuncType time_func)
                : send_func_(func), te_(time_func) {}

        inline uint64_t
        Add(void* msg,
                int32_t msgType,
                double over_time,
                double interval,
                uint64_t max_cnt)
        {
                auto cb = [msg, msgType](void* data, bool has_next)
                {
                        send_func_(msgType, msg);
                        if (!has_next)
                                delete data;
                };
                te_.Add(over_time, cb, nullptr, interval, max_cnt);
        }

        inline void Remove(uint64_t guid) { te_.Remove(guid); }

        inline void Update(void)
        {
                te_.Update();
        }

private :
        TimedEvent te_;
        const SendFuncType send_func_;
};

#endif // __KEY_MSG_HPP__
