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
                  , cb_(cb)
        {
        }

        uint64_t id_;
        double  over_time_;
        float   interval_;
        int32_t loop_count_; // -1 forever
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
        >

        >
> TimedEventListType;

typedef TimedEventListType::nth_index<0>::type            search_by_sequenced;
typedef TimedEventListType::index<by_over_time>::type     search_by_over_time;
typedef TimedEventListType::index<by_id>::type            search_by_id;

class TimedEvent
{
public :
        typedef TimedEventData::TimedEventCallbackType TimedEventCallbackType;

        TimedEvent()
        {
                mRemovedList.reserve(100);
                mAddedList.reserve(100);
        }

        void Update(double now)
        {
                for (auto val : mAddedList)
                {
                        if (nullptr != val)
                                mTimedEventList.push_back(val);
                        else
                                ; // printf("add nullptr == val\n");
                }
                mAddedList.clear();

                search_by_id& seq_id = mTimedEventList.get<by_id>();
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

                search_by_over_time& seq = mTimedEventList.get<by_over_time>();

                // std::vector<TimedEventData*> remove
                auto ie = seq.upper_bound(now);
                auto it = seq.begin();
                printf("count = %lu\n", std::distance(it, ie));
                while (ie != it)
                {
                        TimedEventData* data = *it;
                        if (nullptr != data)
                        {
                                printf("nullptr != data\n");
                                data->cb_(data->id_);

                                if (-1 == data->loop_count_ || --(data->loop_count_) > 0)
                                {
                                        data->over_time_ = now + data->interval_;
                                        printf("before size = %lu\n", seq.size());
                                        seq.replace(it, data);
                                        printf("after  size = %lu\n", seq.size());
                                        // ++it;
                                        // continue;
                                }
                        }
                        ++it;
                }
        }

        inline uint64_t Add(double overTime, TimedEventCallbackType cb, float interval=.0f, int32_t loopCnt=1)
        {
                if (cb && interval>=.0f && (loopCnt>0 || loopCnt==-1))
                {
                        TimedEventData* data = new TimedEventData(overTime, interval, loopCnt, cb);
                        if (nullptr != data)
                        {
                                mAddedList.push_back(data);
                                return data->id_;
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
