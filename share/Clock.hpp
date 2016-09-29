#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <chrono>
#include <string>
#include <ctime>
#include "NonCopyable.hpp"

using namespace std::chrono;

class CTimeCost;
class CClock
{
private :
        CClock() = delete;
        ~CClock() = delete;
public :
        static inline void UpdateTime()
        {
                sNanosecondsNow = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
                time_t now = GetTimeStamp();
                sTimeStampString = ctime(&now);
        }

        static inline uint64_t GetTimeStamp()
        { return sNanosecondsNow / (1000 * 1000 * 1000); }

        static inline uint64_t GetMicroTimeStamp()
        { return sNanosecondsNow / 1000; }

        static inline const std::string& GetTimeToString()
        { return sTimeStampString; }

        static inline const std::string GetTimeToString(uint64_t t)
        { return std::ctime((time_t*)&t); }

        static inline uint64_t GetNanoseconds()
        { return sNanosecondsNow; }

private :
        friend class CTimeCost;

        static inline uint64_t GetTimeStampNow()
        { return duration_cast<seconds>(system_clock::now().time_since_epoch()).count(); }

        static inline uint64_t GetMicroTimeStampNow()
        { return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline uint64_t GetNanosecondsNow()
        { return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline const std::string GetTimeToStringNow()
        {
                time_t now = GetTimeStampNow();
                return std::ctime(&now);
        }

private :
        static uint64_t sNanosecondsNow;
        static std::string sTimeStampString;
};
uint64_t CClock::sNanosecondsNow = 0llu;
std::string CClock::sTimeStampString;

class CTimeCost : public NonCopyable
{
public :
        CTimeCost(std::string prefix="", double sec=.0)
                : mPrefix(prefix), mInterval(sec)
        { mBeginTime = CClock::GetMicroTimeStampNow(); }

        ~CTimeCost()
        {
                double diff = (CClock::GetMicroTimeStampNow() - mBeginTime) / (1000.0 * 1000.0);
                if (diff >= mInterval)
                        printf("%20s cost %lf seconds\n", mPrefix.c_str(), diff);
        }
private :
        uint64_t mBeginTime;
        std::string mPrefix;
        double   mInterval;
};

#endif // __CLOCK_HPP__
