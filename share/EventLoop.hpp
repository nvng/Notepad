#ifndef __EVENT_LOOP_HPP__
#define __EVENT_LOOP_HPP__

#include "ObjectPool.hpp"

template <typename T>
class EventLoop;

template <typename T>
class EventItem
{
public :
        typedef std::function<void(EventItem<T>*)> EventCallbackType;
        void Init(uint64_t guid, T over_tick, T interval, int64_t loop_cnt, EventCallbackType cb)
        {
                guid_ = guid;
                over_tick_ = over_tick;
                interval_ = interval;
                loop_cnt_ = loop_cnt;
                cb_ = cb;
                is_removed_ = false;
                is_set_over_tick_ = false;
        }

        inline uint64_t GetGuid() { return guid_; }
        inline void SetOverTick(T over_tick) { is_set_over_tick_ = true; over_tick_ = over_tick; }
        inline void SetInterval(T interval) { interval_ = interval; }
        inline void Stop() { is_removed_ = true; }

private :
        friend class EventLoop<T>;

        EventCallbackType cb_;
        int64_t loop_cnt_;
        uint64_t guid_;

        T       over_tick_;
        T       interval_;
        bool    is_removed_;
        bool    is_set_over_tick_;
};

template <typename T>
class EventLoop
{
public :
        typedef EventItem<T> EventItemType;
        typedef std::function<T()> GetTickFuncType;

        EventLoop(GetTickFuncType func) : mGetTickFunc(func)
        {
        }

        ~EventLoop()
        {
                for (auto p : mAddedList)
                        delete p;

                for (auto& val : mEventListByOverTick)
                        delete val.second;
        }

        void Update()
        {
                if (!mAddedList.empty())
                {
                        for (EventItemType* data : mAddedList)
                                mEventListByOverTick.insert(std::make_pair(data->over_tick_, data));
                        mAddedList.clear();
                }

                const T now = mGetTickFunc();
                auto ie = mEventListByOverTick.upper_bound(now);
                auto it = mEventListByOverTick.begin();
                for (; ie!=it; ++it)
                {
                        EventItemType* data = it->second;
                        if (!data->is_removed_)
                        {
                                data->cb_(data);
                                if (!data->is_removed_)
                                {
                                        if (!data->is_set_over_tick_)
                                        {
                                                if (-1==data->loop_cnt_ || --(data->loop_cnt_)>0)
                                                        data->SetOverTick(now + data->interval_);
                                        }

                                        if (data->is_set_over_tick_)
                                        {
                                                mAddedList.push_back(data);
                                                data->is_set_over_tick_ = false;
                                                continue;
                                        }
                                        else
                                        {
                                                Stop(data->guid_);
                                        }
                                }
                        }

                        if (data->is_removed_)
                                mEventItemObjectLoop.Free(data);
                }
                mEventListByOverTick.erase(mEventListByOverTick.begin(), ie);
        }

        inline uint64_t Start(T overTick,
                        T interval,
                        int64_t loopCnt,
                        typename EventItemType::EventCallbackType cb)
        {
                static uint64_t sGuid = 0;
                if (cb && interval>=.0 && (loopCnt>0 || LOOP_CNT_FOREVER==loopCnt))
                {
                        EventItemType* ted = mEventItemObjectLoop.Malloc();
                        if (nullptr != ted)
                        {
                                ted->Init(++sGuid, overTick, interval, loopCnt, cb);
                                mEventListByGuid.insert(std::make_pair(ted->guid_, ted));
                                mAddedList.push_back(ted);
                                return ted->guid_;
                        }
                }
                return 0;
        }

        inline void Stop(uint64_t id)
        {
                auto it = mEventListByGuid.find(id);
                if (mEventListByGuid.end() != it)
                {
                        it->second->is_removed_ = true;
                        mEventListByGuid.erase(it);
                }
        }

private :
        std::multimap<T, EventItemType*> mEventListByOverTick;
        std::unordered_map<uint64_t, EventItemType*> mEventListByGuid;

        std::vector<EventItemType*> mAddedList;

        GetTickFuncType mGetTickFunc;
        ObjectPool<EventItemType> mEventItemObjectLoop;
};

typedef EventLoop<double> TimedEventLoop;
typedef EventLoop<uint64_t> FrameEventLoop;

#endif // __EVENT_LOOP_HPP__
