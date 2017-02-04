/* file : time_vs_cclock.cc --> 每次调用 time(NULL) 和 CClock.hpp 类的效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)

int main(void)
{
        Clock cl;
        printf("========== time =========\n");
        uint64_t now = 0;
        {
                CTimeCost t("time");
        for (int32_t i=0; i<MAX_SIZE; ++i)
                now = time(NULL);
        }
        (void)now;

        printf("========== CClock second =========\n");
        cl.UpdateTime();
        {
                CTimeCost t("cclock_second");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        now = cl.GetTimeStamp();
        }
        (void)now;

        // so slow
        /*
        printf("========== CClock now =========\n");
        {
                CTimeCost t("cclock_now");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        now = CClock::GetTimeStampNow();
        }
        (void)now;
        */

        printf("========== CClock string =========\n");
        cl.UpdateTime();
        {
                CTimeCost t("CClock_string");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        std::string nowStr = Clock::GetTimeString_Slow(cl.GetTimeStamp());
                        (void)nowStr;
                }
        }
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
