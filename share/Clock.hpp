#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <chrono>
#include <string>
#include <ctime>
#include "NonCopyable.hpp"

// using namespace std::chrono;

#define GET_TIME_NOW_BY_TYPE(type) std::chrono::duration_cast<std::chrono::type>(std::chrono::system_clock::now().time_since_epoch()).count()

#define MIN(val)       ((val) * 60)
#define HOUR(val)      ((val) * MIN(60))
#define DAY(val)       ((val) * HOUR(24))
#define WEEK(val)      ((val) * DAY(7))

class Clock : public NonCopyable
{
public :
        inline void UpdateTime()
        { mNow = (double)(GET_TIME_NOW_BY_TYPE(microseconds))/(1000.0 * 1000.0); }

        inline int64_t GetTimeStamp() const { return (int64_t)mNow; }
        inline double  GetTime()      const { return mNow; }

        // 不提倡在工程中使用 time string
        static inline const std::string GetTimeString_Slow(int64_t time)
        {
                struct tm lt;
                localtime_r(&time, &lt);

                static const std::string format = "%F %T";
                static const size_t buffSize = sizeof("2000-01-01 00:00:00");
                char buff[buffSize] = {0};
                strftime(buff, buffSize, "%F %T", &lt);

                return buff;
        }

        // 除年和月外，其它时间均可直接换算成秒
        static int64_t TimeAdd(int64_t now, int year, int mon, int sec)
        {
                if (0==year && 0==mon)
                        return now + sec;

                struct tm lt;
                localtime_r(&now, &lt);
                lt.tm_year += year;
                lt.tm_mon  += mon;
                lt.tm_sec  += sec;

                return mktime(&lt);
        }

        static int64_t TimeClear(int64_t now, bool year, bool mon, bool day, bool hour, bool min, bool sec)
        {
                struct tm lt;
                localtime_r(&now, &lt);
                if (year) lt.tm_year = 0;
                if (mon)  lt.tm_mon  = 0;
                if (day)  lt.tm_mday = 1;
                if (hour) lt.tm_hour = 0;
                if (min)  lt.tm_min  = 0;
                if (sec)  lt.tm_sec  = 0;
                return mktime(&lt);
        }

        static int64_t TimeSet(int year, int mon, int sec)
        {
                if (0==year && 0==mon)
                        return sec;

                struct tm lt = { 0 };
                lt.tm_year = year - 1900;
                lt.tm_mon  = mon - 1;
                lt.tm_sec  = sec;
                return mktime(&lt);
        }

        static inline int64_t GetTimeStampNow_Slow() { return GET_TIME_NOW_BY_TYPE(seconds); }
        static inline double  GetTimeNow_Slow()      { return GET_TIME_NOW_BY_TYPE(microseconds)/(1000.0*1000.0); }

private :
        double mNow;
};

#undef GET_TIME_NOW_BY_TYPE

class CTimeCost : public NonCopyable
{
public :
        CTimeCost(const std::string& prefix, double interval=.0)
                : mPrefix(prefix), mInterval(interval)
        {
                mBeginTime = clock();
        }

        ~CTimeCost()
        {
                clock_t diff = clock() - mBeginTime;
                if (diff >= mInterval)
                        printf("%30s cost %lfs %ld ticks\n", mPrefix.c_str(), (double)diff/CLOCKS_PER_SEC, diff);
        }

private :
        const std::string mPrefix;
        clock_t mBeginTime;
        double  mInterval;
};

#endif // __CLOCK_HPP__
