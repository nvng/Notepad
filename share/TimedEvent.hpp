#ifndef __TIMED_EVENT_HPP__
#define __TIMED_EVENT_HPP__

#include <map>
#include <vector>
#include <functional>

class TimedEventData
{
public :
        typedef std::function<void(uint64_t)> TimedEventCallbackType;
        TimedEventData(double over_time,
                        double interval,
                        int32_t loop_count,
                        TimedEventCallbackType cb)
                : id_(++s_id_)
                  , over_time_(over_time)
                  , interval_(interval)
                  , loop_count_(loop_count)
                  , is_removed_(false)
                  , is_stop_(false)
                  , cb_(cb)
        {
        }

        uint64_t id_;
        double  over_time_;
        float   interval_;
        int32_t loop_count_; // -1 forever
        bool    is_removed_;
        bool    is_stop_;
        TimedEventCallbackType cb_;

private :
        static uint64_t s_id_;
};

uint64_t TimedEventData::s_id_ = 0;

#include <boost/multi_index_container.hpp>

#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include <boost/multi_index/member.hpp>

struct by_over_time {};
struct by_id {};
struct by_removed {};

typedef boost::multi_index::multi_index_container <
        TimedEventData*,
        boost::multi_index::indexed_by <

        boost::multi_index::sequenced<>,

        boost::multi_index::ordered_non_unique<
        boost::multi_index::tag<by_over_time>,
        boost::multi_index::member<TimedEventData, double, &TimedEventData::over_time_>
        >,

        boost::multi_index::hashed_unique <
        boost::multi_index::tag<by_id>,
        boost::multi_index::member<TimedEventData, uint64_t, &TimedEventData::id_>
        >,

        boost::multi_index::ordered_non_unique <
        boost::multi_index::tag<by_removed>,
        boost::multi_index::member<TimedEventData, bool, &TimedEventData::is_removed_>
        >

        >
> TimedEventListType;
typedef TimedEventListType::nth_index<0>::type            search_by_sequenced;
typedef TimedEventListType::index<by_over_time>::type     search_by_over_time;
typedef TimedEventListType::index<by_id>::type            search_by_id;
typedef TimedEventListType::index<by_removed>::type       search_by_removed;

class TimedEvent
{
public :
        typedef TimedEventData::TimedEventCallbackType TimedEventCallbackType;

        void Update(double now)
        {
                search_by_over_time& seq = mTimedEventList.get<by_over_time>();

                auto ie = seq.upper_bound(now);
                auto it = seq.begin();
                while (ie != it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                        {
                                if (data->is_stop_ && data->is_removed_)
                                {
                                        ++it;
                                        continue;
                                }

                                data->cb_(data->id_);

                                if (!data->is_removed_ && (-1 == data->loop_count_ || --(data->loop_count_) > 0))
                                {
                                        data->over_time_ = now + data->interval_;
                                        seq.replace(it, data);
                                        ++it;
                                        continue;
                                }
                        }

                        delete data;
                        it = seq.erase(it);
                }

                search_by_removed& seq_removed = mTimedEventList.get<by_removed>();
                auto range = seq_removed.equal_range(true);
                for (auto it=range.first; range.second!=it; ++it)
                        delete *it;
                seq_removed.erase(range.first, range.second);
        }

        inline uint64_t Add(double overTime, TimedEventCallbackType cb, float interval=.0f, int32_t loopCnt=1)
        {
                if (cb && interval>=.0f && (loopCnt>0 || loopCnt==-1))
                {
                        TimedEventData* data = new TimedEventData(overTime, interval, loopCnt, cb);
                        if (nullptr != data)
                        {
                                mTimedEventList.push_back(data);
                                return data->id_;
                        }
                }
                return 0;
        }

        inline bool Remove(uint64_t id)
        {
                search_by_id& seq = mTimedEventList.get<by_id>();
                auto it = seq.find(id);
                if (seq.end() != it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                        {
                                data->is_removed_ = true;
                                seq.replace(it, data);
                                return true;
                        }
                }
                return false;
        }

        inline void Stop(uint64_t id)
        {
                search_by_id& seq = mTimedEventList.get<by_id>();
                auto it = seq.find(id);
                if (seq.end() != it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                                data->is_stop_ = true;
                }
        }

        inline bool Resume(uint64_t id, double now)
        {
                search_by_id& seq = mTimedEventList.get<by_id>();
                auto it = seq.find(id);
                if (seq.end() != it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                        {
                                data->is_stop_ = false;
                                data->over_time_ = now + data->interval_;
                                seq.replace(it, data);
                                return true;
                        }
                }
                return false;
        }

        /*
        inline void Remove(uint64_t id)
        {
                search_by_id& seq = mTimedEventList.get<by_id>();
                auto it = seq.find(id);
                if (seq.end() != it)
                {
                        delete *it;
                        seq.erase(it);
                }
        }
        */

private :
        TimedEventListType mTimedEventList;
};

#endif // __TIMED_EVENT_HPP__
