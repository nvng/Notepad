double GetNow()
{
        return (double)CClock::GetMicroTimeStamp() / (1000.0 * 1000.0);
}

void testTimedEvent()
{
        TimedEventLoop te(GetNow);
        CClock::UpdateTime();

        auto func1 = [](TimedEventLoop::EventItemType* eventData)
        {
                static int cnt = 0;
                printf("event triggered guid[%lu] cnt[%d] now[%f]\n", eventData->GetGuid(), ++cnt, GetNow());
                if (cnt >= 5)
                {
                        cnt = 0;
                        eventData->Stop();
                }
        };

        // for (int i=0; i<10; ++i)
        te.Start(GetNow()+1, 1.0, 10, func1);
        te.Start(GetNow()+10, 1.0, 3, func1);

        while (true)
        {
                CClock::UpdateTime();

                te.Update();
                // std::this_thread::sleep_for(std::chrono::microseconds(15000));
        }
}

uint64_t gFrameCnt = 0;

uint64_t GetFrameCnt() { return gFrameCnt; }

void testFrameEvent()
{
        FrameEventLoop fel(GetFrameCnt);
        auto func1 = [](FrameEventLoop::EventItemType* eventData)
        {
                static int cnt = 0;
                printf("event triggered guid[%lu] cnt[%d] now[%lu]\n", eventData->GetGuid(), ++cnt, GetFrameCnt());
                if (cnt >= 5)
                {
                        eventData->Stop();
                        cnt = 0;
                }
        };
        printf("func1 size = %lu\n", sizeof(func1));
        auto func2 = std::function<double()>();
        printf("func2 size = %lu\n", sizeof(func2));
        printf("function size = %lu\n", sizeof(std::function<double()>));

        fel.Start(GetFrameCnt()+100, 1000*1000*100, 10, func1);

        while (true)
        {
                ++gFrameCnt;
                fel.Update();
        }
}

int main(void)
{
        printf("size = %lu\n", sizeof(FrameEventLoop::EventItemType));
        printf("function size = %lu\n", sizeof(FrameEventLoop::GetTickFuncType));

        printf("size = %lu\n", sizeof(TimedEventLoop::EventItemType));
        printf("function size = %lu\n", sizeof(TimedEventLoop::GetTickFuncType));

        // testTimedEvent();
        testFrameEvent();

        return 0;
}
