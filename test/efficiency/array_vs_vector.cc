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
        uint64_t begin = CClock::GetMicroTimeStampNow();
        int32_t* array = new int32_t[MAX_SIZE];
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                array[randList[i]] = 0;
#else
                array[i] = 0;
#endif
        PRINT_TIME_COST(array_create);

        int32_t tmp = 0;
        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                tmp = array[randList[i]];
#else
                tmp = array[i];
#endif
        PRINT_TIME_COST(array_find);
        (void)tmp;

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                array[randList[i]] = 0;
#else
                array[i] = 0;
#endif
        PRINT_TIME_COST(array_erase);

        delete[] array;
}

void vectorOperation(IntListType& randList)
{
        uint64_t begin = CClock::GetMicroTimeStampNow();
        std::vector<void*> pointerList(MAX_SIZE, NULL);
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                pointerList[randList[i]] = NULL;
#else
                pointerList[i] = NULL;
#endif
        PRINT_TIME_COST(vector_create);

        void* tmp = nullptr;
        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                tmp = pointerList[randList[i]];
#else
                tmp = pointerList[i];
#endif
        PRINT_TIME_COST(vector_find);
        (void)tmp;

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
#ifdef USE_RAND_LIST
                pointerList[randList[i]] = NULL;
#else
                pointerList[i] = NULL;
#endif
        PRINT_TIME_COST(vector_erase);
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
