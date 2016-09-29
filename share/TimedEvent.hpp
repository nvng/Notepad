#ifndef __TIMED_EVENT_HPP__
#define __TIMED_EVENT_HPP__

#include <map>
#include <vector>
#include <functional>

struct STimedEventData
{
        typedef std::function<void()> TimedEventCallbackType;
        STimedEventData(double over_time,
                        double interval,
                        TimedEventCallbackType cb,
                        int32_t loop_count)
                : over_time_(over_time)
                  interval_(interval_)
                  , cb_(cb)
                  , loop_count_(loop_count)
        {
        }

        double over_time_;
        double interval_;
        TimedEventCallbackType cb_;
        int32_t loop_count_; // -1 forever
};

class TimedEvent
{
public :
        typedef STimedEventData::TimedEventCallbackType TimedEventCallbackType;

        void Update(double now)
        {
                std::vector<STimedEventData*> tmpList;

                auto ie = mTimedEventList.upper_bound(now);
                auto it = mTimedEventList.begin();
                for (; ie!=it; ++it)
                {
                        STimedEventData* data = it->second;
                        if (nullptr == data)
                                continue;

                        data->cb_();

                        if (-1 == data->loop_count_ || --(data->loop_count_) > 0)
                                tmpList.push_back(data);
                }

                mTimedEventList.erase(mTimedEventList.begin(), ie);
                for (auto val : tmpList)
                {
                        val->over_time_ = now + val->interval_;
                        mTimedEventList.insert(std::make_pair(val->over_time_, val));
                }
                tmpList.clear();
        }

        inline bool Add(STimedEventData* data)
        {
                if (nullptr != data && data->cb_
                                && data->interval_ > .0
                                && (data->loop_count_>0 || -1==data->loop_count_))
                {
                        mTimedEventList.insert(std::make_pair(data->over_time_, data));
                        return true;
                }
                return false;
        }

private :
        typedef std::multimap<double, STimedEventData*> TimedEventListType;
        TimedEventListType mTimedEventList;
};

#endif // __TIMED_EVENT_HPP__
