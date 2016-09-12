/*
*/

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 100)

int main(void)
{
        int a = 8;
        int b = 7;
        int c;

        {
                CTimeCost t("max");
                for (uint64_t i=0; i<MAX_SIZE; ++i)
                        c = std::max(a, b);
        }

        {
                CTimeCost t("if");
                for (uint64_t i=0; i<MAX_SIZE; ++i)
                        if (a > b)
                                c = a;
                        else
                                c = b;
        }

        {
                CTimeCost t("?:");
                for (uint64_t i=0; i<MAX_SIZE; ++i)
                        c = a>b ? a : b;
        }

        (void)c;

        return 0;
}
