int64_t gCnt = 0;
Clock cl;

int main(void)
{
        FrameControl fc(cl, (int64_t)60);

        auto func = []() { return cl.GetTime(); };
        TimedEventLoop tel(func);

        tel.Start(cl.GetTime()+1, 1.0, -1, [](TimedEventLoop::EventItemType* eventData)
                        {
                                // printf("frameCnt[%ld] now[%f]\n", gCnt, fc.GetCurrentFrameTime());
                                printf("frameCnt[%ld] now[%s\b]\n", gCnt, Clock::GetTimeString_Slow(cl.GetTimeStamp()).c_str());
                                gCnt = 0;
                        });

        cl.UpdateTime();
        int64_t now = cl.GetTimeStamp();
        printf("now = %s\n", Clock::GetTimeString_Slow(now).c_str());

        printf("added = %s\n", Clock::GetTimeString_Slow(Clock::TimeAdd(now, 2, 3, DAY(3)+HOUR(3)+MIN(3)+3)).c_str());
        printf("added = %s\n", Clock::GetTimeString_Slow(Clock::TimeAdd(now, 2, 3, DAY(3)+MIN(3)+3)).c_str());
        // int64_t diff = Clock::TimeAdd(0, 0, 0, DAY(3)+MIN(3)+3);
        // printf("added = %s\n", Clock::GetTimeString_Slow(Clock::TimeAdd(now, 0, 0, diff)).c_str());
        // printf("set time = %s\n", Clock::GetTimeString_Slow(Clock::TimeSet(2001, 7, DAY(8)+HOUR(16)+MIN(52)+3)).c_str());
        // printf("set time = %s\n", Clock::GetTimeString_Slow(Clock::TimeSet(2001, 7, 8, 8, 8, 8)).c_str());

        /*
        int64_t baseTime = Clock::TimeSet(2000, 1, DAY(1)+HOUR(5));
        printf("baseTime = %s\n", Clock::GetTimeString_Slow(baseTime).c_str());
        for (int i=0; i<30; ++i)
                printf("time = %s\n", Clock::GetTimeString_Slow(Clock::TimeAdd(baseTime, 0, i, 0)).c_str());
                */

        bool arr[][6] =
        {
                {false, false, false, false, false, true},
                {false, false, false, false, true, true},
                {false, false, false, true, true, true},
                {false, false, true, true, true, true},
                {false, true, true, true, true, true},
                {true, true, true, true, true, true},
        };

        const int arrSize = sizeof(arr)/sizeof(arr[0]);
        // printf("arrSize = %d\n", arrSize);
        for (int i=0; i<arrSize; ++i)
        {
                int64_t cleardTime = Clock::TimeClear(now, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5]);
                printf("cleardTime = %s\n", Clock::GetTimeString_Slow(cleardTime).c_str());
        }

        {
                CTimeCost t("TimeAdd");
                for (int i=0; i<1000*1000; ++i)
                        Clock::TimeAdd(now, 0, 3, DAY(3)+HOUR(3)+MIN(3)+3);
        }

        {
                CTimeCost t("TimeAdd2");
                for (int i=0; i<1000*1000; ++i)
                        Clock::TimeAdd(now, 0, 0, DAY(3)+HOUR(3)+MIN(3)+3);
        }

        return 0;

        while (1)
        {
                ++gCnt;
                fc.StartOneFrame();
                tel.Update();
                std::this_thread::sleep_for(std::chrono::microseconds(50000));
                // printf("now = %lf\n", fc.GetCurrentFrameTime());
                break;
        }

        return 0;
}
