// #define MAX_LOOP_CNT    (1000 * 1000 * 10)
#define MAX_LOOP_CNT    (1000 * 100)
#define TIMES   (60)
// * 100)

class Test
{
public :
        Test() : mIsStart(false) {}
        void Update()
        {
                mIsStart = true;
        }

        bool mIsStart;
};

int32_t g_cnt = 0;
std::vector<int32_t> testList;

int32_t arr[2];

inline void callBack(void* data, bool has_next)
{
        // printf("id[%-3lu] time = %s", *(uint64_t*)data, CClock::GetTimeToStringNow().c_str());
        // printf("id[%-3lu] time = %lf\n", *(uint64_t*)data, (double)CClock::GetMicroTimeStampNow()/(1000.0 * 1000.0));
        ++g_cnt;
        // for (int i=0; i<100; ++i)
        {
                // arr[0] = g_cnt;
                // arr[0] = 0;
                /*
                testList.push_back(g_cnt);
                testList.clear();
                */
        }

        /*
        if (!has_next)
                delete (uint64_t*)data;
                */
}

int main(void)
{
        Clock cl;
        TimedEventLoop t(std::bind(&Clock::GetTimeStamp, &cl));
        srand(time(NULL));
        cl.UpdateTime();

        int64_t now = cl.GetTimeStamp();
        printf("now = %s", Clock::GetTimeString_Slow(now).c_str());
        (void)now;

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

                // uint64_t* mid = new uint64_t;
                // *mid = t.Start(now, callBack, mid, 0.0, TIMES);
        }

        /*
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
        */

        {
                cl.UpdateTime();
                CTimeCost t_cost("1 times");
                for (int i=0; i<TIMES; ++i)
                        t.Update();
                printf("cnt = %d\n", g_cnt);
        }

        std::vector<Test*> UpdateTestList;
        UpdateTestList.reserve(MAX_LOOP_CNT);
        for (int i=0; i<MAX_LOOP_CNT; ++i)
        {
                Test* t = new Test();
                UpdateTestList.push_back(t);
        }

        {
                CTimeCost t_cost("update");
                for (int i=0; i<TIMES; ++i)
                {
                        for (auto t : UpdateTestList)
                                t->Update();
                }
        }

        return 0;
}
