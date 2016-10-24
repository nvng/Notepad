#define MAX_COUNT       (1000 * 1000)

int gThreadCount = 0;
int gPerThreadCount = 0;

void doThread(int idx)
{
        char* p = nullptr;
        {
                CTimeCost t("new");
                for (int i=0; i<gPerThreadCount; ++i)
                        p = new char[1024];
                printf("%d ", idx);
        }
        (void)p;
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                printf("Usage : [%s] thread_count\n", argv[0]);
                return 0;
        }

        gThreadCount = std::max(atoi(argv[1]), 0);
        gPerThreadCount = MAX_COUNT / gThreadCount;
        std::vector<std::thread*> threadList;
        for (int i=0; i<gThreadCount; ++i)
        {
                std::thread* th = new std::thread(doThread, i);
                threadList.push_back(th);
        }

        for (auto th : threadList)
                th->join();

        return 0;
}
