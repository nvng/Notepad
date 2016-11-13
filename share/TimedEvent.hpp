#ifndef __TIMED_EVENT_HPP__
#define __TIMED_EVENT_HPP__

#include <vector>
#include <functional>

class TimedEventData
{
public :
        typedef std::function<void(void*, bool)> TimedEventCallbackType;
        TimedEventData(double over_time,
                        double interval,
                        int32_t loop_count,
                        TimedEventCallbackType cb)
                : guid_(++s_guid_)
                  , over_time_(over_time)
                  , interval_(interval)
                  , loop_count_(loop_count)
                  , data_(nullptr)
                  , cb_(cb)
        {
        }

        uint64_t guid_;
        double   over_time_;
        double   interval_;
        int32_t  loop_count_; // -1 forever
        void*    data_;
        TimedEventCallbackType cb_;

private :
        static uint64_t s_guid_;
};

uint64_t TimedEventData::s_guid_ = 0;

#include <boost/multi_index_container.hpp>

#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include <boost/multi_index/member.hpp>

struct by_over_time {};
struct by_guid {};

typedef boost::multi_index::multi_index_container <
        TimedEventData*,
        boost::multi_index::indexed_by <

        boost::multi_index::sequenced<>,

        boost::multi_index::ordered_non_unique<
        boost::multi_index::tag<by_over_time>,
        boost::multi_index::member<TimedEventData, double, &TimedEventData::over_time_>
        >,

        boost::multi_index::hashed_unique <
        boost::multi_index::tag<by_guid>,
        boost::multi_index::member<TimedEventData, uint64_t, &TimedEventData::guid_>
        >

        >
> TimedEventListType;

typedef TimedEventListType::nth_index<0>::type            search_by_sequenced;
typedef TimedEventListType::index<by_over_time>::type     search_by_over_time;
typedef TimedEventListType::index<by_guid>::type            search_by_guid;

class TimedEvent
{
public :
        typedef TimedEventData::TimedEventCallbackType TimedEventCallbackType;

        ~TimedEvent()
        {
                for (auto& val : mAddedList)
                        delete val;

                search_by_sequenced& seq = mTimedEventList.get<0>();
                for (auto& val : seq)
                        delete val;
        }

        void Update(double now)
        {
                for (auto val : mAddedList)
                {
                        if (nullptr != val)
                                mTimedEventList.push_back(val);
                }
                mAddedList.clear();

                auto& seq_id = mTimedEventList.get<by_guid>();
                for (auto id : mRemovedList)
                {
                        auto it = seq_id.find(id);
                        if (seq_id.end() != it)
                        {
                                delete *it;
                                seq_id.erase(it);
                        }
                }
                mRemovedList.clear();

                search_by_over_time& seq_over_time = mTimedEventList.get<by_over_time>();
                auto ie = seq_over_time.upper_bound(now);
                printf("count = %lu\n", std::distance(seq_over_time.begin(), ie));
                for (auto it=seq_over_time.begin(); ie!=it; ++it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                        {
                                bool has_next = -1==data->loop_count_ || --(data->loop_count_)>0;
                                data->cb_(data->data_, has_next);
                                if (has_next)
                                {
                                        data->over_time_ = now + data->interval_;
                                        mAddedList.push_back(data);
                                }
                                else
                                {
                                        delete data;
                                }
                        }
                }
                seq_over_time.erase(seq_over_time.begin(), ie);
        }

        inline uint64_t
        Add(double overTime
           , TimedEventCallbackType cb
           , void* data
           , double interval
           , int32_t loopCnt)
        {
                if (cb && interval>=.0f && (loopCnt>0 || loopCnt==-1))
                {
                        TimedEventData* ted = new TimedEventData(overTime, interval, loopCnt, cb);
                        if (nullptr != ted)
                        {
                                ted->data_ = data;
                                mAddedList.push_back(ted);
                                return ted->guid_;
                        }
                }
                return 0;
        }

        inline void Remove(uint64_t id)
        {
                mRemovedList.push_back(id);
        }

private :
        TimedEventListType mTimedEventList;
        std::vector<uint64_t> mRemovedList;
        std::vector<TimedEventData*> mAddedList;
};

#endif // __TIMED_EVENT_HPP__
