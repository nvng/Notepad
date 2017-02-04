#include <map>
#include <vector>
#include <functional>

#include <boost/lambda/lambda.hpp>

#define MAX_LOOP_CNT (1000 * 1000)

#if 0

/*
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
typedef TimedEventListType::index<by_guid>::type          search_by_guid;
*/

struct SChangeOvertime
{
        SChangeOvertime(double over_time) : over_time_(over_time) {}
        inline void operator() (TimedEventData*& data)
        {
                data->over_time_ = over_time_;
        }
private :
        double over_time_;
};
#endif

int main(void)
{
#if 0
        assert(false);

        TimedEventListType testList;

        /*
        for (int i=0; i<MAX_LOOP_CNT; ++i)
        {
                TimedEventData* data = new TimedEventData(1.0+i, i, i, [](uint64_t){});
                testList.push_back(data);
        }
        */

        /*
        search_by_over_time& seq = testList.get<by_over_time>();
        for (auto& val : seq)
        {
                printf("guid[%lu] over_time[%lf]\n", val->guid_, val->over_time_);
        }
        */

#if 0
        printf("==================================================\n");
        int cnt = 0;
        auto it = seq.begin();
        /*
        for (; seq.end()!=it; ++it)
        {
                ++cnt;
                if (5 == cnt)
                {
                        seq.modify_key(it, boost::lambda::_1 = 9999.0);
                        TimedEventData* data = *it;
                        printf("guid[%lu] over_time[%lf]\n", data->guid_, data->over_time_);
                        // seq.modify(it, SChangeOvertime(9999.0));
                }
        }
        */

        for (; seq.end()!=it; ++it)
        {
                ++cnt;
                auto tmp = it;
                // seq.modify_key(it, boost::lambda::_1 = (*it)->over_time_+cnt);
                seq.modify(tmp, SChangeOvertime((*tmp)->over_time_+cnt));
        }
#endif

        {
                auto& seqTest = testList.get<by_over_time>();
                CTimeCost t("modify_key");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {
                        auto it = seqTest.begin();
                        // seqTest.modify(it, SChangeOvertime((*it)->over_time_+MAX_LOOP_CNT));
                        seqTest.modify_key(it, boost::lambda::_1 = (*it)->over_time_+MAX_LOOP_CNT);
                }
        }

        {
                auto& seqTest = testList.get<by_over_time>();
                CTimeCost t("erase");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {

                        auto data = *(seqTest.begin());
                        seqTest.erase(seqTest.begin());
                        data->over_time_ = data->over_time_ + MAX_LOOP_CNT;
                        testList.push_back(data);
                        // printf("size = %lu\n", seqTest.size());

                }
        }

        /*
        printf("==================================================\n");
        for (auto& val : testList.get<by_over_time>())
        {
                printf("guid[%lu] over_time[%lf]\n", val->guid_, val->over_time_);
        }
        */
#endif

        return 0;
}
