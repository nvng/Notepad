#define THREAD_CNT      (3)

#define MAX_ITEM_CNT    (1000 * 1000 * 10)
// #define MAX_ITEM_CNT    (10)

#include "DoubleQueue2.hpp"
#include <atomic>

DoubleQueue2 gDoubleQueue;
std::atomic_int_fast64_t g_cnt(0);
std::atomic_bool flag(false);

void tryDeal(int32_t idx)
{
        while (true)
        {
                void* val = gDoubleQueue.TryGet();
                if (nullptr == val)
                        printf("nullptr == val\n");
                /*
                else
                        printf("thread[%d] val nullptr\n", idx);
                        */
                // std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
}

void waitDeal(int32_t idx)
{
        while (!flag) {}

        while (true)
        {
                void* val = gDoubleQueue.WaitGet();
                if (nullptr == val)
                        printf("nullptr == val\n");
                // printf("thread[%d] val[%d]\n", idx, *val);
                ++g_cnt;
                // delete (uint64_t*)val;
                // std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
}


int main(void)
{
        std::vector<std::thread*> threadList;
        for (int i=0; i<THREAD_CNT; ++i)
        {
                threadList.push_back(new std::thread(waitDeal, i));
                // threadList.push_back(new std::thread(tryDeal, i));
        }

        // uint64_t cnt = 0;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        uint64_t* data_ = new uint64_t(1);
        flag = true;
        CTimeCost* t_cost = new CTimeCost("abc");
        {
                CTimeCost t("push");
                for (int i=0; i<MAX_ITEM_CNT; ++i)
                        gDoubleQueue.PushItem(data_);
        }
        printf("def\n");

        while (true)
        {
                // printf("g_cnt = %lu\n", g_cnt);
                // printf("max_cnt = %lu\n", max_cnt);
                if (g_cnt >= MAX_ITEM_CNT)
                {
                        delete t_cost;
                        break;
                }
        }

        return 0;

#if 0
        uint64_t old_time = 0;
        uint64_t old_cnt = 0;
        while (true)
        {
                CClock::UpdateTime();
                // std::this_thread::sleep_for(std::chrono::microseconds(15000));
                // std::this_thread::sleep_for(std::chrono::seconds(1));
                // std::this_thread::sleep_for(std::chrono::microseconds(1));


                const uint64_t now = CClock::GetTimeStamp();
                if (now != old_time)
                {
                        old_time = now;
                        printf("cnt = %lu\n", cnt - old_cnt);
                        old_cnt = cnt;
                }
        }
#endif

        for (auto th : threadList)
        {
                th->join();
                delete th;
        }

        return 0;
}
