#include "pre_compiled.h"

#define MAX_COUNT       (1000 * 1000)

std::mutex m;
int g_count = 0;

void threadDoSomething(int idx)
{
        {
                CTimeCost t("lock_guard mutex");
                for (int i=0; i<MAX_COUNT; ++i)
                {
                        std::lock_guard<std::mutex> lock(m);
                        ++g_count;
                }
                printf("thread[%d] ", idx);
        }
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                printf("Usage : %s thread count\n", argv[0]);
                return 0;
        }

        std::vector<std::thread*> threadList;
        const int threadCount = atoi(argv[1]);
        for (int i=0; i<threadCount; ++i)
                threadList.push_back(new std::thread(threadDoSomething, i+1));

        for (auto thread : threadList)
                thread->join();
        printf("g_count = %d\n", g_count);

        return 0;
}
