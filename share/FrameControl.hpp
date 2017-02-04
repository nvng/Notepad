#ifndef __FRAME_CONTROL_HPP__
#define __FRAME_CONTROL_HPP__

#include "Clock.hpp"
#include "NonCopyable.hpp"
#include <thread>

class FrameControl : public NonCopyable
{
public :
        FrameControl(Clock& clock, double diff)
                : mClock(clock), mFrameDiffTime(diff), mPreFrameBeginTime(0.0)
        {
        }

        inline void StartOneFrame()
        {
                ++mFrameCnt;
                mClock.UpdateTime();
                double now = mClock.GetTime();

                double diff = now - mPreFrameBeginTime;
                mPreFrameBeginTime = now;
                if (diff < mFrameDiffTime)
                {
                        std::this_thread::sleep_for(std::chrono::microseconds((int64_t)((mFrameDiffTime - diff)*1000*1000)));
                        mClock.UpdateTime();
                        mPreFrameBeginTime = mClock.GetTime();
                }
        }

        inline uint64_t GetFrameCnt() { return mFrameCnt; }
private :
        Clock& mClock;
        const double mFrameDiffTime;
        double mPreFrameBeginTime;
        uint64_t mFrameCnt;
};

#endif // __FRAME_CONTROL_HPP__
