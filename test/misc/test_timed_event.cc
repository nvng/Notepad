#define GET_NOW() ((double)CClock::GetMicroTimeStamp() / (1000.0 * 1000.0))

int main(void)
{
        TimedEvent te;
        CClock::UpdateTime();

        std::function<void(uint64_t)> func1 = [](uint64_t id)
        {
                static int cnt = 0;
                ++cnt;
                // printf("call back now = %lf\n", GET_NOW());
                if (cnt >= 5)
                {
                        cnt = 0;
                        /*
                        te.Remove(id);
                        auto func2 = [&](uint64_t id)
                        {
                                ++cnt;
                                // printf("22222 call back now = %lf\n", GET_NOW());
                                if (cnt >= 3)
                                {
                                        cnt = 0;
                                        te.Remove(id);
                                        te.Add(GET_NOW()+1, func1, 1.0, 10);
                                }
                        };

                        te.Add(GET_NOW()+2, func2, 2.0, 5);
                        */
                }
        };

        for (int i=0; i<10; ++i)
                te.Add(GET_NOW()+1, func1, 1.0, 10);

        while (true)
        {
                CClock::UpdateTime();

                te.Update(GET_NOW());
                std::this_thread::sleep_for(std::chrono::microseconds(15000));
        }

        return 0;
}
