/* file : array_vs_vector.cc --> 传统数组 和 vector 效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (65536 * 1000)

typedef std::vector<int64_t> IntListType;

void arrayOperation(IntListType& randList)
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

void vectorOperation(IntListType& randList)
{
        uint64_t begin = CClock::GetMicroTimeStampNow();
        std::vector<void*> pointerList(MAX_SIZE, NULL);
        for (int32_t i=0; i<MAX_SIZE; ++i)
                pointerList[i] = (void*)randList[i];
        PRINT_TIME_COST(vector_create);

        begin = CClock::GetMicroTimeStampNow();
        void* tmp = nullptr;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                tmp = pointerList[i];
        (void)tmp;
        PRINT_TIME_COST(vector_find);

        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                pointerList[i] = NULL;
        PRINT_TIME_COST(vector_erase);
}

int main(void)
{
        srand(time(NULL));

        IntListType gRandList;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                gRandList.push_back(rand());

        printf("========== array ==========\n");
        arrayOperation(gRandList);
        printf("========== vector ==========\n");
        vectorOperation(gRandList);


        return 0;
}
