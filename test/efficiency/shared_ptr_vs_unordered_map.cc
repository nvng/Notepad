/* file : shared_ptr_vs_unordered_map.cc
 * result :
 * desc :
 */

#include "pre_compiled.h"

std::mutex g_mutex;

int main(void)
{
        srand(time(NULL));

        const int32_t times = 1000 * 1000 * 10;
        std::unordered_map<int, int*> umap;

        for (int32_t i=0; i<times; ++i)
                umap.insert(std::make_pair(i, new int));
        printf("umap.size() = %lu\n", umap.size());

        int* p = nullptr;
        {
                CTimeCost t("unordered_map");
                std::unordered_map<int, int*>::iterator it;
                for (int32_t i=0; i<times; ++i)
                {
                        // it = umap.find(i);
                        // std::lock_guard<std::mutex> lock(g_mutex);
                        it = umap.find(i);
                        p = (umap.end() != it) ? it->second : nullptr;
                        if (nullptr == p)
                                printf("abc\n");
                }
        }
        (void)p;

        /*
        std::unordered_map<std::string, int*> strMap;
        char buff[1024] = { 0 };
        for (auto val : umap)
        {
                snprintf(buff, sizeof(buff), "%d", val.first);
                strMap.insert(std::make_pair(buff, new int));
        }

        {
                std::unordered_map<std::string, int*>::iterator it;
                char buff[1024] = { 0 };
                snprintf(buff, sizeof(buff), "%d", times-1);
                printf("key = %s\n", buff);
                std::string key = buff;
                CTimeCost t("unordered_map string");
                for (int32_t i=0; i<times; ++i)
                {
                        // it = umap.find(i);
                        it = strMap.find(key);
                        if (strMap.end() != it)
                        {
                                int* p = it->second;
                                *p = 1;
                        }
                }
        }
        */

        {
                std::shared_ptr<int> spi(new int);
                std::weak_ptr<int> wpi = spi;
                std::shared_ptr<int> tmp;
                CTimeCost t("weak_ptr lock");
                for (int32_t i=0; i<times; ++i)
                {
                        tmp = wpi.lock();
                        if (!tmp)
                                printf("abc\n");
                }
        }

        std::make_shared<int>();

        return 0;
}
