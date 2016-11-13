#include "pre_compiled.h"

std::mutex g_mutex;
std::mutex g_mutex_2;

const int32_t max_count = 1000 * 1000 * 10;
int32_t count_per_thread = 0;
std::unordered_map<int, int*> umap;

void threadDeal(int idx)
{
        int* p = nullptr;
        {
                CTimeCost t("unordered_map");
                std::unordered_map<int, int*>::iterator it;
                for (int32_t i=0; i<count_per_thread; ++i)
                {
                        std::lock_guard<std::mutex> lock(g_mutex);
                        it = umap.find(i);
                        p = (umap.end() != it) ? it->second : nullptr;
                }
                printf("%d ", idx);
        }
        (void)p;

        {
                std::shared_ptr<int> spi(new int);
                std::weak_ptr<int> wpi = spi;
                std::shared_ptr<int> tmp;
                CTimeCost t("weak_ptr lock");
                for (int32_t i=0; i<count_per_thread; ++i)
                {
                        std::lock_guard<std::mutex> lock(g_mutex_2);
                        tmp = wpi.lock();
                }
                printf("%d ", idx);
        }
}

int main(int argc, char* argv[])
{
        if (2 != argc)
        {
                printf("Usage : %s thread count\n", argv[0]);
                return 0;
        }

        const int thread_count = atoi(argv[1]);
        count_per_thread = max_count / thread_count;

        for (int32_t i=0; i<max_count; ++i)
                umap.insert(std::make_pair(i, new int));
        printf("umap.size() = %lu\n", umap.size());

        std::vector<std::thread*> threadList;
        for (int i=0; i<thread_count; ++i)
                threadList.push_back(new std::thread(threadDeal, i));

        for (auto th : threadList)
                th->join();

        return 0;
}
