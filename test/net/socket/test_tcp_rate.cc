#include "pre_compiled.h"

#define SERVER_IP       ("127.0.0.1")
#define SERVER_PORT     (8888)
#define BACK_LOG        (5)
#define BUFF_SIZE       (1024 * 10240)

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

template <typename T>
int net_opt(int fd, void* buf, int left, T opt)
{   
        int opted = 0;
        while(0 < left)
        {   
                int len = opt(fd, (void*)((char*)buf+opted), left, 0); 
                switch (len)
                {   
                case -1 :
                        if (EAGAIN == errno)
                        {
                                printf("if (EAGAIN == errno)\n");
                                continue;
                        }
                        else                 return -1; 
                        break;
                case 0 : 
                        {
                                printf("case 0\n");
                        goto leave;
                        }
                        break;
                default :
                        left  -= len;
                        opted += len;
                        break;
                }   

        }   
leave :
        return opted;
}

int Send(int fd, void* buf, int left)
{
        return net_opt(fd, buf, left, send);
}

int Recv(int fd, void* buf, int left)
{
        return net_opt(fd, buf, left, recv);
}

void server()
{
        int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(-1 != listen_fd);

        struct sockaddr_in server_addr;
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port   = htons(SERVER_PORT);

        int ret = inet_pton(AF_INET, SERVER_IP, (void*)&server_addr.sin_addr);
        assert(-1 != ret);

        int reuse = 1;
        ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
        assert(-1 != ret);

        ret = bind(listen_fd, (SA*)&server_addr, sizeof(SA));
        assert(-1 != ret);

        ret = listen(listen_fd, BACK_LOG);
        assert(-1 != ret);

        char* buff = new char[BUFF_SIZE];
        while (1)
        {
                socklen_t len = sizeof(server_addr);
                int connected_fd = accept(listen_fd, (SA*)&server_addr, &len);
                assert(-1 != connected_fd);

                uint64_t buff_count = 0;
                uint64_t now = CClock::GetTimeStamp() / 1000;
                while (1)
                {
                        ++buff_count;
                        int size = Send(connected_fd, buff, BUFF_SIZE);
                        assert(BUFF_SIZE == size);

                        size = Recv(connected_fd, buff, BUFF_SIZE);
                        assert(BUFF_SIZE == size);

                        uint64_t end = CClock::GetTimeStamp() / 1000;
                        if (end > now)
                        {
                                now = end;
                                printf("buff count %lu\n", buff_count);
                                buff_count = 0;
                        }
                }
        }

        close(listen_fd);
}

void client()
{
        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        assert(-1 != client_fd);

        struct sockaddr_in server_addr;
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port   = htons(SERVER_PORT);

        int ret = inet_pton(AF_INET, SERVER_IP, (void*)&server_addr.sin_addr);
        assert(-1 != ret);

        ret = connect(client_fd, (SA*)&server_addr, sizeof(SA));
        assert(-1 != ret);

        int reuse = 1;
        ret = setsockopt(client_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
        assert(-1 != ret);

        uint64_t buff_count = 0;
        uint64_t now = CClock::GetTimeStamp() / 1000;
        char* buff = new char[BUFF_SIZE];
        while (1)
        {
                ++buff_count;
                int size = Recv(client_fd, buff, BUFF_SIZE);
                assert(BUFF_SIZE == size);

                size = Send(client_fd, buff, BUFF_SIZE);
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
