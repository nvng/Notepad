/* file : select_us.cc --> 使用 select 函数实现微秒级 sleep */

#include <sys/select.h>

#include "pre_compiled.h"

int main(void)
{

        struct timeval tv;
        static uint64_t cnt = 0;

        while (1)
        {
                tv.tv_sec = 0;
                tv.tv_usec = 100;

                static uint64_t old = CClock::GetMicroTimeStampNow();
                select(0, NULL, NULL, NULL, &tv);
                uint64_t now = CClock::GetMicroTimeStampNow();
                printf("%8lu = %lf\n", ++cnt, (now - old) / (1000.0f * 1000.0f));
                old = now;
        }

        return 0;
}
