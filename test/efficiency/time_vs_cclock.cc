/* file : time_vs_cclock.cc --> 每次调用 time(NULL) 和 CClock.hpp 类的效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)

int main(void)
{
        printf("========== time =========\n");
        uint64_t begin = CClock::GetMicroTimeStampNow();
        uint64_t now = 0;
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = time(NULL);
        PRINT_TIME_COST(time);
        (void)now;

        printf("========== CClock second =========\n");
        begin = CClock::GetMicroTimeStampNow();
        CClock::UpdateTime();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = CClock::GetTimeStamp();
        PRINT_TIME_COST(CClock_second);
        (void)now;

        printf("========== CClock nanosecond =========\n");
        begin = CClock::GetMicroTimeStampNow();
        CClock::UpdateTime();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = CClock::GetNanoseconds();
        PRINT_TIME_COST(CClock_nanosecond);
        (void)now;

        // so slow
        printf("========== CClock now =========\n");
        begin = CClock::GetMicroTimeStampNow();
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = CClock::GetTimeStampNow();
        PRINT_TIME_COST(CClock_now);
        (void)now;

        printf("========== CClock string =========\n");
        begin = CClock::GetMicroTimeStampNow();
        CClock::UpdateTime();
        for (int32_t i=0; i<MAX_SIZE; ++i)
        {
                const char* nowStr = CClock::GetTimeToString();
                (void)nowStr;
        }
        PRINT_TIME_COST(CClock_string);
        (void)now;

        /*
        // so slow
        printf("========== CClock now string =========\n");
        begin = CClock::GetMicroTimeStampNow();
        CClock::UpdateTime();
        for (int32_t i=0; i<MAX_SIZE; ++i)
        {
                const char* nowStr = CClock::GetTimeToStringNow();
                (void)nowStr;
        }
        PRINT_TIME_COST(CClock_now_string);
        (void)now;
        */

        return 0;
}
