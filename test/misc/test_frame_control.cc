int main(void)
{
        Clock clock;
        clock.UpdateTime();

        FrameControl fc(clock, 0.015);
        // FrameControl fc((uint64_t)100);
        TimedEventLoop tel([&](){ return clock.GetTime(); });
        tel.Start(clock.GetTime()+1, 1.0, -1, [&](TimedEventLoop::EventItemType* eventData)
                        {
                                static uint64_t oldCnt = 0;
                                printf("frame per second[%lu] now[%lf]\n", fc.GetFrameCnt() - oldCnt, clock.GetTime());
                                oldCnt = fc.GetFrameCnt();
                        });
        while (1)
        {
                fc.StartOneFrame();

                tel.Update();

                std::this_thread::sleep_for(std::chrono::microseconds(25000));
        }

        return 0;
}
