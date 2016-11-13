int main(void)
{
        TimedEvent t;
        srand(time(NULL));
        CClock::UpdateTime();

        printf("now = %s\n", CClock::GetTimeToString().c_str());
        uint64_t now = CClock::GetTimeStamp();

        bool is_start = false;
        uint64_t cnt = 0;
        for (int i=0; i<1000 * 1000; ++i)
        {
                t.Add(now, [&](void* data, bool has_next)
                {
                        is_start = true;
                        ++cnt;
                        // std::this_thread::sleep_for(std::chrono::microseconds(1));
                        // printf("timed now = %s", CClock::GetTimeToString().c_str());
                }, nullptr, 1.0, 2);
        }

        while (1)
        {
                CClock::UpdateTime();
                uint64_t now = CClock::GetTimeStamp();

                CTimeCost* t_cost = nullptr;
                if (is_start)
                {
                        printf("start\n");
                        t_cost = new CTimeCost("cost");
                }
                t.Update(now);
                if (nullptr != t_cost)
                {
                        delete t_cost;
                        printf("cnt = %lu\n", cnt);
                        return 0;
                }
        }

        return 0;
}
