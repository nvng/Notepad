#ifndef __FRAME_CONTROL_HPP__
#define __FRAME_CONTROL_HPP__

#include "Clock.hpp"
#include "NonCopyable.hpp"
#include <thread>

class FrameControl : public NonCopyable
{
public :
        typedef CClock::ValueType time_type;
        FrameControl(double diff)
                : mFrameDiffMicroTime(diff*1000.0*1000.0)
                  , mPreFrameBeginTime(0)
        {
        }

        inline void StartOneFrame()
        {
                ++mFrameCnt;
                CClock::UpdateTime();
                time_type now = CClock::GetMicroTimeStamp();

                time_type diff = now - mPreFrameBeginTime;
                mPreFrameBeginTime = now;
                if (diff < mFrameDiffMicroTime)
                {
                        std::this_thread::sleep_for(microseconds(mFrameDiffMicroTime - diff));
                        CClock::UpdateTime();
                        mPreFrameBeginTime = CClock::GetMicroTimeStamp();
                }
        }

        inline uint64_t GetFrameCnt() { return mFrameCnt; }

        inline double GetCurrentFrameTime() { return (double)CClock::GetMilliseconds() / 1000.0; }

private :
        const time_type mFrameDiffMicroTime;
        time_type mPreFrameBeginTime;
        uint64_t mFrameCnt;
};

#endif // __FRAME_CONTROL_HPP__
