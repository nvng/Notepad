/* file : time_vs_cclock.cc --> time 函数和 clock 函数效率对比
 * result : time 函数执行效率比 clock 高 50 倍左右。
 * desc : time 获取的是时间，而 clock 获取的是占用 CPU 时间。
 *        没有占用CPU时间，而经历了时间，由 time 会变，clock 不会变。
 *        如：sleep
 */

#include "pre_compiled.h"

#define MAX_COUNT       (1000 * 1000)

int main(void)
{
        {
                CTimeCost t("time");
                for (int i=0; i<MAX_COUNT; ++i)
                        time(NULL);
        }

        // time 获取的是真实时间
        time_t now = time(NULL);
        sleep(1);
        time_t diff1 = time(NULL) - now;
        printf("time_sleep cost = %ld\n", diff1);

        {
                CTimeCost t("clock");
                for (int i=0; i<MAX_COUNT; ++i)
                        clock();
        }

        // clock 获取的是占用 CPU 时间
        clock_t b = clock();
        sleep(1);
        clock_t diff = clock() - b;
        printf("clock_sleep cost = %ld\n", diff);

        return 0;
}
