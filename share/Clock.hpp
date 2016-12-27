#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <chrono>
#include <string>
#include <ctime>
#include "NonCopyable.hpp"

using namespace std::chrono;

#define GET_TIME_BY_TYPE(type) duration_cast<type>(sNow.time_since_epoch()).count()

class CTimeCost;
class CClock
{
private :
        CClock() = delete;
        ~CClock() = delete;
public :
        static inline void UpdateTime()
        {
                sNow = system_clock::now();
                time_t now = GetTimeStamp();
                sTimeStampString = ctime(&now);
        }

        static inline uint64_t GetTimeStamp() { return GET_TIME_BY_TYPE(seconds); }
        static inline uint64_t GetMicroTimeStamp() { return GET_TIME_BY_TYPE(microseconds); }
        static inline uint64_t GetMilliseconds() { return GET_TIME_BY_TYPE(milliseconds); }
        // static inline uint64_t GetDay() { return GET_TIME_BY_TYPE(milliseconds); }
        static inline uint64_t GetNanoseconds() { return GET_TIME_BY_TYPE(nanoseconds); }

        static inline const std::string& GetTimeToString()
        { return sTimeStampString; }

        static inline const std::string GetTimeToString(uint64_t t)
        { return std::ctime((time_t*)&t); }

// private :
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
        static system_clock::time_point sNow;
        static std::string sTimeStampString;
};

system_clock::time_point CClock::sNow;
std::string CClock::sTimeStampString;

class CTimeCost : public NonCopyable
{
public :
        CTimeCost(const char* prefix, double sec=.0)
                : mPrefix(prefix), mInterval(sec)
        { mBeginTime = clock(); }

        ~CTimeCost()
        {
                clock_t diff = clock() - mBeginTime;
                if (diff >= mInterval)
                        printf("%20s cost %lfs %ld ticks\n", mPrefix, (double)diff/CLOCKS_PER_SEC, diff);
        }
private :
        const char* mPrefix;
        clock_t mBeginTime;
        double  mInterval;
};

#endif // __CLOCK_HPP__
