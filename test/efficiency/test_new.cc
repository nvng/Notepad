/* file : test_new.cc --> 大块内存空间的 new 和小块空间的 new 比较。
 * result : 大块空间的 new 更有效率。
 * desc : new 出内存相关 10240 倍，但 new 的时间只相差 10 倍左右。
 */

#define MAX_COUNT       (1000 * 1000)

int main(void)
{
        char* p = nullptr;
        {
                CTimeCost t("new small");
                for (int i=0; i<MAX_COUNT; ++i)
                        p = new char;
        }

        {
                CTimeCost t("new big");
                for (int i=0; i<MAX_COUNT; ++i)
                        p = new char[10*1024];
        }

        (void)p;

        return 0;
}
