#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <chrono>
#include <string>
#include <ctime>
#include "NonCopyable.hpp"

using namespace std::chrono;

#define GET_TIME_BY_TYPE(type) duration_cast<type>(sNow.time_since_epoch()).count()

class CClock
{
private :
        CClock() = delete;
        ~CClock() = delete;
public :
        typedef uint64_t ValueType;

        static inline void UpdateTime()
        {
                sNow = system_clock::now();
                time_t now = GetTimeStamp();
                sTimeStampString = ctime(&now);
        }

        static inline ValueType GetTimeStamp() { return GET_TIME_BY_TYPE(seconds); }
        static inline ValueType GetMicroTimeStamp() { return GET_TIME_BY_TYPE(microseconds); }
        static inline ValueType GetMilliseconds() { return GET_TIME_BY_TYPE(milliseconds); }
        // static inline ValueType GetDay() { return GET_TIME_BY_TYPE(milliseconds); }
        static inline ValueType GetNanoseconds() { return GET_TIME_BY_TYPE(nanoseconds); }

        static inline const std::string& GetTimeToString()
        { return sTimeStampString; }

        static inline const std::string GetTimeToString(ValueType t)
        { return std::ctime((time_t*)&t); }



        static inline ValueType GetTimeStampNow()
        { return duration_cast<seconds>(system_clock::now().time_since_epoch()).count(); }

        static inline ValueType GetMicroTimeStampNow()
        { return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline ValueType GetNanosecondsNow()
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
