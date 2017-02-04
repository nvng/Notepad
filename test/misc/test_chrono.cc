#define MAX_LOOP_CNT (1000 * 1000)

int main(void)
{
        auto maxD = std::chrono::system_clock::duration::max();
        auto minD = std::chrono::system_clock::duration::min();


        printf("microseconds   den[%ld] num[%ld]\n", std::chrono::microseconds::period::den, std::chrono::microseconds::period::num);
        printf("nanoseconds    den[%ld] num[%ld]\n", std::chrono::nanoseconds::period::den, std::chrono::nanoseconds::period::num);
        printf("minutes den[%ld] num[%ld]\n",        std::chrono::minutes::period::den, std::chrono::minutes::period::num);
        printf("seconds den[%ld] num[%ld]\n",        std::chrono::seconds::period::den, std::chrono::seconds::period::num);
        printf("hours   den[%ld] num[%ld]\n",        std::chrono::hours::period::den, std::chrono::hours::period::num);

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        printf("sizeof of time_point = %lu\n", sizeof(now));

        printf("max = %ld\n", maxD.count());
        printf("min = %ld\n", minD.count());

        typedef std::chrono::duration<int,std::ratio<60*60*24>> days_type;

        uint64_t nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

        uint64_t timeStamp = 0;
        (void)timeStamp;
        {
                CTimeCost t("static");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        timeStamp += nanoSec / (1000 * 1000 * 1000);
        }

        {
                CTimeCost t("cast");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        timeStamp += std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        }
        printf("timeStamp = %lu\n", timeStamp);

        // auto months = std::chrono::duration_cast<mon_type>(now.time_since_epoch()).count();
        auto days = std::chrono::duration_cast<days_type>(now.time_since_epoch()).count();
        printf("days = %d\n", days);

        struct tm* localTimeInfo = nullptr;
        (void)localTimeInfo;
        time_t now_time_t = time(nullptr);
        {
                CTimeCost t("localtime");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        localTimeInfo = localtime(&now_time_t);
        }
        {
                CTimeCost t("mktime");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        now_time_t = mktime(localTimeInfo);
        }

        return 0;
}
