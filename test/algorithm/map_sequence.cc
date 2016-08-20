/* file : map_sequence.cc --> map multimap 为有序，unordered_map unordered_multimap 为无序
 * result : 需要有序的时候，就用 map 吧，unordered_map 在其它方面比 map 好
 * desc : upper_bound 大于 lower_bound 大于等于
 */

#include "pre_compiled.h"
#define MAX_SIZE        (10)

template <typename T>
void mapOperator(T obj)
{
        printf("for range\n");
        for (auto val : obj)
                printf("%4d ", val.first);
        putchar('\n');

        printf("for iterator\n");
        auto it = obj.begin();
        auto ie = obj.end();
        for (; ie!=it; ++it)
                printf("%4d ", it->first);
        putchar('\n');
}

template <typename T>
void mapUpperBound(T obj, int32_t val)
{
        printf("for upper_bound val = %d\n", val);
        auto f = obj.upper_bound(val);
        for (auto i=obj.begin(); f!=i; ++i)
                printf("%4d ", i->first);
        putchar('\n');

        printf("for lower_bound val = %d\n", val);
        f = obj.lower_bound(val);
        for (auto i=obj.begin(); f!=i; ++i)
                printf("%4d ", i->first);
        putchar('\n');
}

int main(void)
{
        srand(time(NULL));
        int32_t tmp = 0;

        std::vector<int32_t> randList(MAX_SIZE, 0);
        for (int32_t i=0; i<MAX_SIZE; ++i)
                randList[i] = rand()%1000;
        tmp = randList[0];

        std::map<int32_t, int32_t> timeEventList;
        std::unordered_map<int32_t, int32_t> timeEventList_2;
        for (auto val : randList)
        {
                timeEventList.insert(std::make_pair(val, 0));
                timeEventList_2.insert(std::make_pair(val, 0));
        }

        printf("============== map ==============\n");
        mapOperator(timeEventList);
        mapUpperBound(timeEventList, tmp);
        printf("============== unordered_map ==============\n");
        mapOperator(timeEventList_2);

        std::multimap<int32_t, int32_t> multi_timeEventList;
        std::unordered_multimap<int32_t, int32_t> multi_timeEventList_2;
        for (int idx=0; idx<4; ++idx)
        {
                for (int i=0; i<3; ++i)
                {
                        multi_timeEventList.insert(std::make_pair(randList[idx], 0));
                        multi_timeEventList_2.insert(std::make_pair(randList[idx], 0));
                }
        }

        printf("============== multimap ==============\n");
        mapOperator(multi_timeEventList);
        mapUpperBound(multi_timeEventList, tmp);
        printf("============== unordered_multimap ==============\n");
        mapOperator(multi_timeEventList_2);
        // mapUpperBound(multi_timeEventList_2, tmp);

        return 0;
}
