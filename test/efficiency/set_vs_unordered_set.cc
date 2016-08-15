/* file : set_vs_unordered_set.cc --> set 和 unordered_set 效率对比 */

#include "pre_compiled.h"

template <typename T>
void testSet(T obj, std::vector<int32_t>& randList)
{
        uint64_t begin = CClock::GetMicroTimeStampNow();
        for (int32_t val : randList)
                obj.insert(val);
        PRINT_TIME_COST(insert);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t val : randList)
                obj.find(val);
        PRINT_TIME_COST(search);

        begin = CClock::GetMicroTimeStampNow();
        uint64_t tmp = 0;
        (void)tmp;
        for (typename T::value_type val : obj)
                tmp = val;
        PRINT_TIME_COST(traversal);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t val : randList)
                obj.erase(val);
        PRINT_TIME_COST(erase);
}

int main(void)
{
        srand(time(NULL));

        std::vector<int32_t> gRandList;
        const int32_t times = 1000 * 1000 * 10;
        for (int32_t i=0; i<times; ++i)
                gRandList.push_back(rand());

        printf("========== unordered_set ==========\n");
        testSet(std::unordered_set<uint64_t>(), gRandList);
        printf("========== set ==========\n");
        testSet(std::set<uint64_t>(), gRandList);

        return 0;
}
