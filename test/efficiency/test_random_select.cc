#define MAX_COUNT (1000 * 1000 * 10)
#define LOOP_COUNT (1000 * 1000)

int main()
{
        srand(time(NULL));
        RandomSelect rs;

        std::vector<int64_t*> newList;
        for (int i=0; i<MAX_COUNT; ++i)
        {
                int64_t* key = new int64_t(i);
                newList.push_back(key);
                rs.Add(1+rand() % 999, key);
        }


                uint64_t maxCount = 0;
#if 0
        {
                int64_t sum = rs.GetSum();
                std::vector<int32_t> tmpList;
                for (int i=0; i<LOOP_COUNT; ++i)
                        tmpList.push_back(rand()%sum);

                CTimeCost t("randomSelect");
                for (int i=0; i<LOOP_COUNT; ++i)
                {
                        g_count = 0;
                        void* key = rs.Get(tmpList[i]);
                        if (nullptr == key)
                                printf("nullptr == key\n");

                        if (g_count > maxCount)
                                maxCount = g_count;
                }
        }
#endif

        printf("maxCount = %lu\n", maxCount);

        for (auto key : newList)
                delete key;

        return 0;
}
