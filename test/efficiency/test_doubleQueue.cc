#define THREAD_CNT      (3)

#include "DoubleQueue2.hpp"

DoubleQueue2<int32_t*> gDoubleQueue;

void waitDeal(int32_t idx)
{
        while (true)
        {
                int32_t* val = gDoubleQueue.WaitGet();
                if (nullptr == val)
                        printf("nullptr == val\n");
                // printf("thread[%d] val[%d]\n", idx, *val);
                delete val;
                std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
}

void tryDeal(int32_t idx)
{
        while (true)
        {
                int32_t* val = nullptr;
                if (gDoubleQueue.TryGet(val))
                {
                        if (nullptr == val)
                                printf("nullptr == val\n");
                        // printf("thread[%d] val[%d]\n", idx, *val);
                }
                /*
                else
                        printf("thread[%d] val nullptr\n", idx);
                        */
                std::this_thread::sleep_for(std::chrono::microseconds(1));
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

        int32_t cnt = 0;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        while (true)
        {
                std::this_thread::sleep_for(std::chrono::microseconds(15000));
                // std::this_thread::sleep_for(std::chrono::seconds(1));
                for (int i=0; i<100; ++i)
                        gDoubleQueue.PushItem(new int32_t(++cnt));
        }

        for (auto th : threadList)
        {
                th->join();
                delete th;
        }

        return 0;
}
