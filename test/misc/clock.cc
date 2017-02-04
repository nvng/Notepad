/* file : clock.cc --> */

#include <ctime>
#include <cstdio>

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)

int main(void)
{
        // printf("time = %ld\n", time(NULL));
        {
                // CTimeCost("time");
                CTimeCost t("time");
                for (int i=0; i<MAX_SIZE; ++i)
                        time(NULL);
        }

        {
                struct timespec ts;
                CTimeCost t("timespec");
                for (int i=0; i<MAX_SIZE; ++i)
                        timespec_get(&ts, TIME_UTC);
        }

        {
                CTimeCost t("chrono");
                for (int i=0; i<MAX_SIZE; ++i)
                        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        /*
        {
                for (int i=0; i<MAX_SIZE; ++i)
                        CClock::GetNanosecondsNow();
        }
        */

        /*
        printf("seconds = %8ld nanoseconds = %8ld\n", ts.tv_sec, ts.tv_nsec);
        printf("seconds = %8ld nanoseconds = %8ld\n", now / (1000 * 1000 * 1000), now % (1000 * 1000 * 1000));
        */

        return 0;
}
