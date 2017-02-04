#define MAX_LOOP_CNT    (1000 * 1000 * 100)
uint64_t gCnt = 0;

void func_c(void)
{
        /*
        for (int i=0; i<10; ++i)
                for (int i=0; i<10; ++i)
                        ++gCnt;
                        */
        rand();
}

int main(void)
{
        {
                auto func = []()
                {
                        /*
                        for (int i=0; i<10; ++i)
                                ++gCnt;
                                */
                        rand();
                };
                CTimeCost t("function");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        func();
        }

        {
                CTimeCost t("func_c");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        func_c();
        }

        {
                CTimeCost t("rand");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        rand();
        }

        printf("gCnt = %lu\n", gCnt);

        return 0;
}
