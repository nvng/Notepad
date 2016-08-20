/* file : ./array_vs_unordered_map.cc --> 传统数组 和 unordered_map 效率对比
 * result : array 的创建、赋值和删除在 unordered_map 10 倍左右，但查找在万倍以上。
 * desc :
 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 10)

void arrayOperation(std::vector<int32_t>& randList)
{
        int32_t* array = nullptr;
        {
                CTimeCost t("create");
                array = new int32_t[MAX_SIZE];
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        array[randList[i]] = i;
        }

        int32_t tmp = 0;
        {
                CTimeCost t("array_find");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        tmp = array[randList[i]];
        }
        (void)tmp;

        {
                CTimeCost t("array erase");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        array[randList[i]] = 0;
        }
}

void unorderedMapOperation(std::vector<int32_t>& randList)
{
        CTimeCost* tmpT = new CTimeCost("unordered_map_create");
        std::unordered_map<int32_t, int32_t*> dataList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                dataList.insert(std::make_pair(randList[i], (int32_t*)NULL));
        delete tmpT;

        std::unordered_map<int32_t, int32_t*>::iterator it;
        {
                CTimeCost t("unordered_map_find");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        it = dataList.find(randList[i]);
        }

        {
                CTimeCost t("unordered_map_erase");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        dataList.erase(randList[i]);
        }
}

int main(void)
{
        srand(time(NULL));

        std::vector<int32_t> gRandList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                gRandList.push_back(rand() % MAX_SIZE);

        printf("========== array ==========\n");
        arrayOperation(gRandList);
        printf("========== unordered_map ==========\n");
        unorderedMapOperation(gRandList);

        return 0;
}
