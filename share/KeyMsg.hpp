#ifndef __KEY_MSG_HPP__
#define __KEY_MSG_HPP__

#include "EventLoop.hpp"

class KeyMsg
{
public :
        typedef std::function<bool(int32_t, void*)> SendFuncType;
        KeyMsg(SendFuncType func, TimedEventLoop::GetTickFuncType time_func)
                : send_func_(func), te_(time_func) {}

        inline uint64_t
        Add(std::shared_ptr<void> msg,
                int32_t msgType,
                double over_time,
                double interval,
                uint64_t max_cnt)
        {
                auto cb = [msg, msgType](TimedEventLoop::EventItemType* eventData)
                {
                        send_func_(msgType, msg.get());
                };
                te_.Start(over_time, interval, max_cnt, cb);
        }

        inline void Remove(uint64_t guid) { te_.Remove(guid); }

        inline void Update(void)
        {
                te_.Update();
        }

private :
        TimedEventLoop te_;
        const SendFuncType send_func_;
};

#endif // __KEY_MSG_HPP__
