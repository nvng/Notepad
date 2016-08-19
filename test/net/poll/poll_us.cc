/* file : poll_us.cc --> 使用 poll 函数实现微秒级 sleep */

#include "pre_compiled.h"

#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void)
{
        uint64_t cnt = 0;
        uint64_t now = 0;
        uint64_t old = 0;

        struct pollfd tmp_fds[10];
        memset(tmp_fds, 0x00, sizeof(tmp_fds));
        tmp_fds[0].fd = socket(AF_INET, SOCK_STREAM, 0);
        tmp_fds[0].events = POLLIN;

        while (1)
        {
                old = CClock::GetMicroTimeStampNow();
                poll(tmp_fds, 11, 1000 * 1000);
                now = CClock::GetMicroTimeStampNow();
                printf("%8lu = %lf\n", ++cnt, (now - old) / (1000.0f * 1000.0f));
                old = now;
        }

        return 0;
}
