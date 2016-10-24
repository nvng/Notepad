#define MAX_COUNT (1000 * 1000)
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

        {
                int64_t sum = rs.GetSum();
                CTimeCost t("randomSelect");
                for (int i=0; i<LOOP_COUNT; ++i)
                {
                        void* key = rs.Get(rand()%sum);
                        if (nullptr == key)
                                printf("nullptr == key\n");
                }
        }

        for (auto key : newList)
                delete key;

        return 0;
}
