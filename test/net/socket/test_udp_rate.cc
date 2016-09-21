#include "pre_compiled.h"

#define SERVER_IP       ("127.0.0.1")
#define SERVER_PORT     (8888)
#define CLIENT_PORT     (7777)
#define BACK_LOG        (5)
#define BUFF_SIZE       (1024 * 10)

typedef struct sockaddr SA;

void test_sock_opt(int fd)
{
        socklen_t len = sizeof(SA);
        int buff_size = 0;
        int ret = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, &len);
        assert(-1 != ret);
        printf("recv buff size = %d\n", buff_size);

        buff_size = 3000;
        ret = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, len);
        assert(-1 != ret);

        ret = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, &len);
        assert(-1 != ret);
        printf("recv buff size = %d\n", buff_size);

        ret = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buff_size, &len);
        assert(-1 != ret);
        printf("send buff size = %d\n", buff_size);

        buff_size = 3000;
        ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buff_size, len);
        assert(-1 != ret);

        ret = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buff_size, &len);
        assert(-1 != ret);
        printf("send buff size = %d\n", buff_size);
}

void server()
{
        int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(-1 != server_fd);

        struct sockaddr_in server_addr;
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port   = htons(SERVER_PORT);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        /*
        int ret = inet_pton(AF_INET, SERVER_IP, (void*)&server_addr.sin_addr);
        assert(-1 != ret);
        */

        int ret = bind(server_fd, (SA*)&server_addr, sizeof(server_addr));
        assert(-1 != ret);

        struct sockaddr_in peerAddr;
        socklen_t len = sizeof(peerAddr);
        bzero(&server_addr, len);

        uint64_t buff_count = 0;
        char* buff = new char[BUFF_SIZE];
        uint64_t now = CClock::GetTimeStamp() / 1000;
        while (1)
        {
                ++buff_count;
                int size = recvfrom(server_fd, buff, BUFF_SIZE, 0, (SA*)&peerAddr, &len);
                // size = sendto(server_fd, buff, BUFF_SIZE, 0, (SA*)&peerAddr, sizeof(peerAddr));
                assert(BUFF_SIZE == size);

                uint64_t end = CClock::GetTimeStamp() / 1000;
                if (end > now)
                {
                        now = end;
                        printf("buff count %lu\n", buff_count);
                        buff_count = 0;
                }

                /*
                ++buff_count;
                printf("111111111\n");
                int n = recvfrom(server_fd, buff, BUFF_SIZE, 0, (struct sockaddr*)&peerAddr, &len);
                printf("111111111\n");
                assert(BUFF_SIZE == n);

                n = sendto(server_fd, buff, BUFF_SIZE, 0, (struct sockaddr *)&peerAddr, sizeof(peerAddr));
                printf("111111111\n");
                assert(BUFF_SIZE == n);
                */
        }

        close(server_fd);
}

void client()
{
        int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(-1 != client_fd);

        struct sockaddr_in server_addr;
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port   = htons(SERVER_PORT);

        int ret = inet_pton(AF_INET, SERVER_IP, (void*)&server_addr.sin_addr);
        assert(-1 != ret);

        ret = connect(client_fd, (SA*)&server_addr, sizeof(server_addr));
        assert(-1 != ret);

        /*
        ret = bind(client_fd, (SA*)&server_addr, sizeof(server_addr));
        assert(-1 != ret);
        */

        char* buff = new char[BUFF_SIZE];
        uint64_t buff_count = 0;
        socklen_t len = sizeof(server_addr);
        (void)len;
        uint64_t now = CClock::GetTimeStamp() / 1000;
        while (1)
        {
                ++buff_count;
                int size = sendto(client_fd, buff, BUFF_SIZE, 0, (SA*)&server_addr, sizeof(server_addr));
                // size = recvfrom(client_fd, buff, BUFF_SIZE, 0, (SA*)&server_addr, &len);
                assert(BUFF_SIZE == size);

                uint64_t end = CClock::GetTimeStamp() / 1000;
                if (end > now)
                {
                        now = end;
                        printf("buff count %lu\n", buff_count);
                        buff_count = 0;
                }
        }

        close(client_fd);
}

int main(int argc, char* argv[])
{
        if (argc != 2)
        {
                printf("Usage :\n%s 1 --> server\n%s 2 --> client\n",
                                argv[0], argv[0]);
                return -1;
        }

        std::thread t([]()
        {
                struct timeval tv;
                while (1)
                {
                        tv.tv_sec = 0;
                        tv.tv_usec = 1000;

                        select(0, NULL, NULL, NULL, &tv);
                        CClock::UpdateTime();
                }
        });

        switch(atoi(argv[1]))
        {
        case 1 : server(); break;
        case 2 : client(); break;
        default :
                break;
        }

        t.join();

        return 0;
}
