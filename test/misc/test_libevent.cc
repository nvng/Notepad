#include <event.h>

double GetNow()
{
        return Clock::GetTimeNow_Slow();
}

double lasttime = 0.0;

static void
timeout_cb(int fd, short event, void* arg)
{
        struct timeval tv;
        struct event* timeout = (struct event*)arg;
        double newtime = GetNow();

        printf("%s : called at %lf : %lf\n", "timeout_cb", newtime, newtime-lasttime);
        lasttime = newtime;

        evutil_timerclear(&tv);
        tv.tv_sec = 2;
        event_add(timeout, &tv);
}

int main(void)
{
        struct event timeout;
        struct timeval tv;

        event_init();
        evtimer_set(&timeout, timeout_cb, &timeout);
        evutil_timerclear(&tv);
        tv.tv_sec = 2;

        event_add(&timeout, &tv);
        lasttime = GetNow();

        event_dispatch();

        return 0;
}
