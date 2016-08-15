#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <chrono>
#include <string>
#include <ctime>

using namespace std::chrono;

class CClock
{
public :
        static inline void UpdateTime()
        { sNanosecondsNow = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline uint64_t GetTimeStamp()
        { return sNanosecondsNow / (1000 * 1000); }

        static inline uint64_t GetMicroTimeStamp()
        { return sNanosecondsNow / 1000; }

        static inline const char* GetTimeToString()
        {
                time_t now = GetTimeStamp();
                return std::ctime(&now);
        }

        static inline uint64_t GetNanoseconds()
        { return sNanosecondsNow; }

        static inline uint64_t GetTimeStampNow()
        { return duration_cast<seconds>(system_clock::now().time_since_epoch()).count(); }

        static inline uint64_t GetMicroTimeStampNow()
        { return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline uint64_t GetNanosecondsNow()
        { return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count(); }

        static inline const char* GetTimeToStringNow()
        {
                time_t now = GetTimeStampNow();
                return std::ctime(&now);
        }

private :
        static uint64_t sNanosecondsNow;
};
uint64_t CClock::sNanosecondsNow = 0llu;

#endif // __CLOCK_HPP__
