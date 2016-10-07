#define GET_NOW() ((double)CClock::GetMicroTimeStamp() / (1000.0 * 1000.0))

int main(void)
{
        TimedEvent te;
        CClock::UpdateTime();

        double now = GET_NOW();
        bool is_stop = false;
        uint64_t id = te.Add(now+1, [&](uint64_t id)
        {
                static int cnt = 0;
                ++cnt;
                printf("call back now = %lf\n", GET_NOW());
                if (cnt == 5)
                {
                        is_stop = true;
                        te.Stop(id);
                }
        }, 1.0f, 10);

        static int32_t cnt = 0;
        while (true)
        {
                CClock::UpdateTime();

                te.Update(GET_NOW());
                std::this_thread::sleep_for(std::chrono::microseconds(16667));

                if (is_stop)
                {
                        ++cnt;
                        if (cnt >= 180)
                        {
                                is_stop = false;
                                bool ret = te.Resume(id, GET_NOW());
                                printf("ret = %s\n", ret ? "true" : "false");
                        }
                }
        }

        return 0;
}
