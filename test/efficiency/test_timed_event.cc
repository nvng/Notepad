// #define MAX_LOOP_CNT    (1000 * 1000 * 10)
#define MAX_LOOP_CNT    (1000 * 1000)
#define TIMES   (9)

int32_t g_cnt = 0;

void callBack(void* data, bool has_next)
{
        // printf("id[%-3lu] time = %s", *(uint64_t*)data, CClock::GetTimeToStringNow().c_str());
        // printf("id[%-3lu] time = %lf\n", *(uint64_t*)data, (double)CClock::GetMicroTimeStampNow()/(1000.0 * 1000.0));
        ++g_cnt;
}

int main(void)
{
        TimedEvent t(CClock::GetTimeStamp);
        srand(time(NULL));
        CClock::UpdateTime();

        printf("now = %s", CClock::GetTimeToString().c_str());
        uint64_t now = CClock::GetTimeStamp();

        for (int i=0; i<MAX_LOOP_CNT; ++i)
        {
                /*
                t.Add(now, [&](void* data, bool has_next)
                {
                        ++g_cnt;
                        // std::this_thread::sleep_for(std::chrono::microseconds(1));
                        // printf("timed now = %s", CClock::GetTimeToString().c_str());
                }, nullptr, 0.0, TIMES);
                */

                uint64_t* mid = new uint64_t;
                *mid = t.Add(now, callBack, mid, 0.0, TIMES);
        }

        CTimeCost* t_cost = nullptr;
        int32_t loop_cnt = 0;
        while (1)
        {
                // printf("loop_cnt = %d\n", ++loop_cnt);
                CClock::UpdateTime();
                if (nullptr == t_cost)
                        t_cost = new CTimeCost("main update");
                {
                        t.Update();
                }

                if (g_cnt >= MAX_LOOP_CNT * TIMES)
                {
                        delete t_cost;
                        printf("cnt = %d\n", g_cnt);
                        break;
                }

                if (loop_cnt >= TIMES)
                {
                        // printf("cnt = %d\n", g_cnt);
                        break;
                }
        }

        return 0;
}
