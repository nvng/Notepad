/* file : time_vs_just_get.cc --> 每次调用 time(NULL) 和 只调用一次，然后 get 效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 100)

// #define GetTimeNow()      (now)

static int32_t now = 0;

inline int32_t GetTimeNow()
// int32_t GetTimeNow()
{
        // static int32_t now = time(NULL); // 为什么放在这里效率低，而放在函数外效率高呢？
        return now;
}

int main(void)
{
        printf("========== time =========\n");
        uint64_t begin = CClock::GetMicroTimeStampNow();
        int32_t now = 0;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = time(NULL);
        PRINT_TIME_COST(time);
        (void)now;

        printf("========== get =========\n");
        begin = CClock::GetMicroTimeStampNow();
        now = time(NULL);
        int32_t tmp = 0;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                tmp = GetTimeNow();
        PRINT_TIME_COST(get);
        (void)tmp;

        return 0;
}
