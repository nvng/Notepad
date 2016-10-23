#include "pre_compiled.h"

#define LOOP_TIMES      (1000 * 1000 * 1000)
inline int Inc_inline()
{
        int val = 0;
        for (int i=0; i<LOOP_TIMES; ++i)
                ++val;
        return val;
}

int Inc()
{
        int val = 0;
        for (int i=0; i<LOOP_TIMES; ++i)
                ++val;
        return val;
}

#define INC(val) \
        do { \
                for (int i=0; i<LOOP_TIMES; ++i) \
                        ++val; \
        } while (0)

int main(void)
{
        {
                CTimeCost t("inline");
                for (int i=0; i<LOOP_TIMES; ++i)
                        Inc_inline();
        }

        {
                CTimeCost t("not inline");
                for (int i=0; i<LOOP_TIMES; ++i)
                        Inc();
        }

        int inc = 0;
        {
                CTimeCost t("define");
                for (int i=0; i<LOOP_TIMES; ++i)
                        INC(inc);
        }

        return 0;
}
