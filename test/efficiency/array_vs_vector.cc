/* file : array_vs_vector.cc --> 传统数组 和 vector 效率对比
 * result : 差不多，有需要可以再测试一下
 * desc : 
 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 100)
#define USE_RAND_LIST

typedef std::vector<int64_t> IntListType;

void arrayOperation(IntListType& randList)
{
        int32_t* array = nullptr;
        {
                CTimeCost t("array_create");
                array = new int32_t[MAX_SIZE];
                for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                        array[randList[i]] = 0;
#else
                        array[i] = 0;
#endif
        }

        int32_t tmp = 0;
        {
                CTimeCost t("array_find");
                for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                        tmp = array[randList[i]];
#else
                        tmp = array[i];
#endif
        }
        (void)tmp;

        {
                CTimeCost t("array_erase");
                for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                        array[randList[i]] = 0;
#else
                        array[i] = 0;
#endif
        }

        delete[] array;
}

void vectorOperation(IntListType& randList)
{
        CTimeCost* tmpT = new CTimeCost("vector_create");
        std::vector<void*> pointerList(MAX_SIZE, NULL);
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                pointerList[randList[i]] = NULL;
#else
                pointerList[i] = NULL;
#endif
        delete tmpT;

        void* tmp = nullptr;
        {
                CTimeCost t("vector_find");
                for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                        tmp = pointerList[randList[i]];
#else
                        tmp = pointerList[i];
#endif
        }
        (void)tmp;

        {
                CTimeCost t("vector_erase");
                for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                        pointerList[randList[i]] = NULL;
#else
                        pointerList[i] = NULL;
#endif
        }
}

int main(void)
{
        srand(time(NULL));

        IntListType gRandList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                gRandList.push_back(rand() % MAX_SIZE);

        printf("========== array ==========\n");
        arrayOperation(gRandList);
        printf("========== vector ==========\n");
        vectorOperation(gRandList);


        return 0;
}
