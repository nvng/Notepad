int main(void)
{
        CClock::UpdateTime();

        FrameControl fc(0.015);
        TimedEventLoop tel([&](){ return fc.GetCurrentFrameTime(); });
        tel.Start(fc.GetCurrentFrameTime()+1, 1.0, -1, [&](TimedEventLoop::EventItemType* eventData)
                        {
                                static uint64_t oldCnt = 0;
                                printf("frame per second[%lu] now[%lf]\n", fc.GetFrameCnt() - oldCnt, fc.GetCurrentFrameTime());
                                oldCnt = fc.GetFrameCnt();
                        });
        while (1)
        {
                fc.StartOneFrame();

                tel.Update();

                std::this_thread::sleep_for(microseconds(30000));
        }

        return 0;
}
