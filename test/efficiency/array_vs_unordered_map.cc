/* file : ./array_vs_unordered_map.cc --> 传统数组 和 unordered_map 效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (65536)

void arrayOperation(std::vector<int32_t>& randList)
{
        uint64_t begin = CClock::GetMicroTimeStampNow();
        int32_t* array = new int32_t[MAX_SIZE];
        for (int32_t i=0; i<MAX_SIZE; ++i)
                array[i] = randList[i];
        PRINT_TIME_COST(array_create);

        begin = CClock::GetMicroTimeStampNow();
        int32_t tmp = 0;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                tmp = array[i];
        (void)tmp;
        PRINT_TIME_COST(array_find);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                array[i] = 0;
        PRINT_TIME_COST(array_erase);
}

void unorderedMapOperation(std::vector<int32_t>& randList)
{
        uint64_t begin = CClock::GetMicroTimeStampNow();
        std::unordered_map<int32_t, int32_t*> dataList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                dataList.insert(std::make_pair(i, (int32_t*)NULL));
        PRINT_TIME_COST(unordered_map_create);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
        {
                std::unordered_map<int32_t, int32_t*>::iterator it = dataList.find(i);
                (void)it;
        }
        PRINT_TIME_COST(unordered_map_find);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                dataList.erase(randList[i]);
        PRINT_TIME_COST(unordered_map_erase);
}

int main(void)
{
        srand(time(NULL));

        std::vector<int32_t> gRandList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                gRandList.push_back(rand());

        printf("========== array ==========\n");
        arrayOperation(gRandList);
        printf("========== unordered_map ==========\n");
        unorderedMapOperation(gRandList);

        return 0;
}
