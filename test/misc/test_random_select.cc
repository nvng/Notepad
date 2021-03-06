#define MAX_COUNT (1000 * 100)

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

        const int64_t sum = rs.GetSum();
        for (int64_t i=0; i<sum; ++i)
        {
                void* key = rs.Get(i);
                if (nullptr == key)
                        printf("nullptr == key\n");
        }

        for (auto key : newList)
                delete key;

        return 0;
}
