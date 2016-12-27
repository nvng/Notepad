#ifndef __TIMED_EVENT_MAP_HPP__
#define __TIMED_EVENT_MAP_HPP__

static const int32_t LOOP_CNT_FOREVER = -1;
static bool g_is_set_over_time = false;
class TimedEvent_1;
class TimedEventData_1
{
public :
        typedef std::function<void(TimedEventData_1*)> TimedEventCallbackType;
        void Init(uint64_t guid, double over_time, double interval, int64_t loop_cnt, TimedEventCallbackType cb)
        {
                guid_ = guid;
                over_time_ = over_time;
                interval_ = interval;
                loop_cnt_ = loop_cnt;
                cb_ = cb;
                is_removed_ = false;
        }

        inline uint64_t GetGuid() { return guid_; }
        inline void SetOverTime(double over_time) { g_is_set_over_time = true; over_time_ = over_time; }
        inline void SetInterval(double interval) { interval_ = interval; }
        inline void Stop() { is_removed_ = true; }

private :
        friend class TimedEvent_1;
        double over_time_;
        double interval_;
        int64_t loop_cnt_;
        bool is_removed_;
        TimedEventCallbackType cb_;

        uint64_t guid_;
};

class TimedEvent_1
{
public :
        typedef std::function<double()> GetTimeFuncType;
        TimedEvent_1(GetTimeFuncType func) : mGetTimeFunc(func)
        {
                mAddedList.reserve(100);
        }

        ~TimedEvent_1()
        {
                mAddedList.clear();
                mTimedEventListByGuid.clear();
                mTimedEventListByOverTime.clear();
        }

        void Update()
        {
                if (!mAddedList.empty())
                {
                        for (TimedEventData_1* data : mAddedList)
                                mTimedEventListByOverTime.insert(std::make_pair(data->over_time_, data));
                        mAddedList.clear();
                }

                const double now = mGetTimeFunc();
                auto ie = mTimedEventListByOverTime.upper_bound(now);
                auto it = mTimedEventListByOverTime.begin();
                for (; ie!=it; ++it)
                {
                        TimedEventData_1* data = it->second;
                        if (!data->is_removed_)
                        {
                                data->cb_(data);
                                if (!data->is_removed_)
                                {
                                        if (!g_is_set_over_time)
                                        {
                                                if (LOOP_CNT_FOREVER==data->loop_cnt_ || --(data->loop_cnt_)>0)
                                                        data->SetOverTime(now + data->interval_);
                                        }

                                        if (g_is_set_over_time)
                                        {
                                                mAddedList.push_back(data);
                                                g_is_set_over_time = false;
                                                continue;
                                        }
                                        else
                                        {
                                                Stop(data->guid_);
                                        }
                                }
                        }

                        if (data->is_removed_)
                                delete data;
                }
                mTimedEventListByOverTime.erase(mTimedEventListByOverTime.begin(), ie);
        }

        uint64_t Start(double overTime,
                        double interval,
                        int64_t loopCnt,
                        TimedEventData_1::TimedEventCallbackType cb)
        {
                static uint64_t sGuid = 0;
                if (cb && interval>=.0 && (loopCnt>0 || LOOP_CNT_FOREVER==loopCnt))
                {
                        TimedEventData_1* ted = new TimedEventData_1();
                        if (nullptr != ted)
                        {
                                ted->Init(++sGuid, overTime, interval, loopCnt, cb);
                                mTimedEventListByGuid.insert(std::make_pair(ted->guid_, ted));
                                mAddedList.push_back(ted);
                                return ted->guid_;
                        }
                }
                return 0;
        }

        void Stop(uint64_t id)
        {
                auto it = mTimedEventListByGuid.find(id);
                if (mTimedEventListByGuid.end() != it)
                {
                        it->second->is_removed_ = true;
                        mTimedEventListByGuid.erase(it);
                }
        }

        inline size_t GetSize() { return mTimedEventListByOverTime.size(); }

private :
        std::multimap<double, TimedEventData_1*> mTimedEventListByOverTime;
        std::unordered_map<uint64_t, TimedEventData_1*> mTimedEventListByGuid;
        std::vector<TimedEventData_1*> mAddedList;

        GetTimeFuncType mGetTimeFunc;
};

#endif // __TIMED_EVENT_MAP_HPP__
