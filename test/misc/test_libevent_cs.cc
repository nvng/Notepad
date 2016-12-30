#include <event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

#define LISTEN_PORT (8888)
#define LISTEN_BACKLOG (128)

uint64_t gCnt = 0;
uint64_t gFrameCnt = 0;

double GetNow()
{
        // return (double)CClock::GetMicroTimeStampNow() / (1000.0 * 1000.0);
        return 0.0;
}

#if 0
static void
timeout_cb(int fd, short event, void* arg)
{
        ++gFrameCnt;
        struct timeval tv;
        struct event* timeout = (struct event*)arg;

        /*
        static uint64_t oldCnt = 0;
        printf("recv %lu per second\n", gCnt - oldCnt);
        oldCnt = gCnt;
        */

        std::this_thread::sleep_for(milliseconds(15));

        evutil_timerclear(&tv);
        tv.tv_sec = 0;
        tv.tv_usec = 15000;
        event_add(timeout, &tv);
}
#endif

static void
timeout_ps_cb(int fd, short event, void* arg)
{
        struct timeval tv;
        struct event* timeout = (struct event*)arg;

        static uint64_t oldCnt = 0;
        printf("recv %lu per second\n", gCnt - oldCnt);
        oldCnt = gCnt;
        /*
        printf("frame cnt %lu per second\n", gFrameCnt - oldCnt);
        oldCnt = gFrameCnt;
        */

        evutil_timerclear(&tv);
        tv.tv_sec = 1;
        event_add(timeout, &tv);
}

void read_cb(struct bufferevent* bev, void* arg)
{
        static size_t MAX_LINE = 10240;
        char line[MAX_LINE] = {0};
        // evutil_socket_t fd = bufferevent_getfd(bev);

        ++gCnt;
        int n;
        while ((n = bufferevent_read(bev, line, MAX_LINE)) > 0)
        {
                line[n] = '\0';
                // printf("fd = %u, read line : %s\n", fd, line);
                bufferevent_write(bev, line, n);
        }
}

void write_cb(struct bufferevent* bev, void* arg)
{
}

void error_cb(struct bufferevent* bev, short event, void* arg)
{
        evutil_socket_t fd = bufferevent_getfd(bev);
        printf("error : fd = %u\n", fd);

        if (event & BEV_EVENT_TIMEOUT)
        {
                printf("Timed out\n");
        }
        else if (event & BEV_EVENT_EOF)
        {
                printf("connection closed\n");
        }
        else if (event & BEV_EVENT_ERROR)
        {
                printf("some other error\n");
        }
        else
        {
                printf("unknow error\n");
        }

        bufferevent_free(bev);
}

void client_read_cb(evutil_socket_t fd, short event, void* arg)
{
        static size_t MAX_LINE = 10240;
        char line[MAX_LINE] = {0};
        int n;
        while ((n = read(fd, line, MAX_LINE)) > 0)
        {
                line[n] = '\0';
                // printf("fd = %u, read line : %s\n", fd, line);
                write(fd, line, n);
        }
}

void do_accept_cb(evutil_socket_t listener, short event, void* arg)
{
        struct event_base* base = (struct event_base*)arg;
        struct sockaddr_in sin;
        socklen_t slen;
        evutil_socket_t fd = accept(listener, (struct sockaddr*)&sin, &slen);
        assert(-1 != fd);
        printf("accept : fd = %d\n", fd);

        struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
        bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

void accept_cb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int socklen, void* arg)
{
        event_base* base = (event_base*)arg;
        bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
        bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

void StartServer()
{
        struct sockaddr_in server_addr;
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(LISTEN_PORT);
        inet_aton("127.0.0.1", &server_addr.sin_addr);

        struct event_base* base = event_base_new();
        struct evconnlistener* listener = evconnlistener_new_bind(base, accept_cb, base,
                        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                        10, (struct sockaddr*)&server_addr, sizeof(server_addr));

        struct event timeout_ps;
        evtimer_set(&timeout_ps, timeout_ps_cb, &timeout_ps);
        event_base_set(base, &timeout_ps);
        struct timeval tv;
        evutil_timerclear(&tv);
        tv.tv_sec = 1;
        event_add(&timeout_ps, &tv);

        event_base_dispatch(base);
        evconnlistener_free(listener);
        event_base_free(base);

#if 0
        evutil_socket_t listener = socket(AF_INET, SOCK_STREAM, 0);
        assert(-1 != listener);

        evutil_make_listen_socket_reuseable(listener); // 端口重用

        struct sockaddr_in sin;
        bzero(&sin, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_port = htons(LISTEN_PORT);

        int ret = bind(listener, (struct sockaddr*)&sin, sizeof(sin));
        (void)ret;
        assert(-1 != ret);

        ret = listen(listener, LISTEN_BACKLOG);
        assert(-1 != ret);

        evutil_make_socket_nonblocking(listener); // 设置为非阻塞模式

        struct event_base* base = event_base_new();
        assert(NULL != base);

        struct event* listen_event = event_new(base, listener, EV_READ|EV_PERSIST, do_accept_cb, (void*)base);
        event_add(listen_event, NULL);

                struct timeval tv;
        /*
                struct event timeout;
                evtimer_set(&timeout, timeout_cb, &timeout);
                event_base_set(base, &timeout);
                evutil_timerclear(&tv);
                tv.tv_sec = 0;
                tv.tv_usec = 15000;
                event_add(&timeout, &tv);
                */

                struct event timeout_ps;
                evtimer_set(&timeout_ps, timeout_ps_cb, &timeout_ps);
                event_base_set(base, &timeout_ps);
                evutil_timerclear(&tv);
                tv.tv_sec = 1;
                event_add(&timeout_ps, &tv);

        event_base_dispatch(base);

        return;
#endif
}

void StartClient()
{
#if 0
        struct event_base* base = event_base_new();
        assert(NULL != base);
        for (int i=0; i<10; ++i)
        {
                evutil_socket_t connect_fd = socket(AF_INET, SOCK_STREAM, 0);
                assert(-1 != listener);

                struct sockaddr_in sin;
                bzero(&sin, sizeof(sin));
                sin.sin_family = AF_INET;
                sin.sin_addr.s_addr = inet_addr("127.0.0.1");
                sin.sin_port = htons(LISTEN_PORT);

                evutil_make_socket_nonblocking(connect_fd); // 设置为非阻塞模式

                struct bufferevent* conn = bufferevent_socket_new(base, connect_fd, BEV_OPT_CLOSE_ON_FREE);
                bufferevent_socket_connect(conn, (struct sockaddr*)&sin, sizeof(sin));

                static char* msg = new char[102400];
                for (int i=0; i<102400; ++i)
                        msg[i] = 'a';
                bufferevent_write(conn, msg, 10240);

                bufferevent_setcb(conn, read_cb, NULL, error_cb, base);
                bufferevent_enable(conn, EV_READ|EV_WRITE);

                // event_add(conn, NULL);

                /*
                struct event* ev_sockfd = event_new(base, connect_fd, EV_READ|EV_PERSIST, client_read_cb, NULL);
                event_add(ev_sockfd, NULL);
                */
        }

        struct event timeout;
        evtimer_set(&timeout, timeout_cb, &timeout);
        event_base_set(base, &timeout);
        struct timeval tv;
        evutil_timerclear(&tv);
        tv.tv_sec = 1;
        event_add(&timeout, &tv);

        event_base_dispatch(base);
        printf("End\n");


        /*
        // struct event* connect_event = event_new(base, connect_fd, EV_READ|EV_PERSIST, read_cb, (void*)base);
        // event_add(conn, NULL);
        event_base_dispatch(base);

        struct event* listen_event = event_new(base, connect_fd, EV_READ|EV_PERSIST, do_connected_cb, (void*)base);
        event_add(listen_event, NULL);
        event_base_dispatch(base);
        */
#endif

        struct sockaddr_in conn_addr;
        bzero(&conn_addr, sizeof(conn_addr));
        conn_addr.sin_family = AF_INET;
        conn_addr.sin_port = htons(LISTEN_PORT);
        inet_aton("127.0.0.1", &conn_addr.sin_addr);

        struct event_base* base = event_base_new();
        for (int i=0; i<10000; ++i)
        {
                struct bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
                bufferevent_socket_connect(bev, (struct sockaddr*)&conn_addr, sizeof(conn_addr));

                const char* buff = "aaaaa";
                bufferevent_write(bev, buff, sizeof("aaaaa"));

                bufferevent_setcb(bev, read_cb, NULL, NULL, bev);
                bufferevent_enable(bev, EV_READ | EV_PERSIST);
        }

        event_base_dispatch(base);

        return;
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                printf("Usage : %s [1 server 2 client]\n", argv[0]);
                return -1;
        }

        switch (atoi(argv[1]))
        {
        case 1 : StartServer(); break;
        case 2 : StartClient(); break;
        default :
                break;
        }

        return 0;
}
