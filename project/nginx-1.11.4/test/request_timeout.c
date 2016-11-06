/**
 * gcc -Wall -g -o request_timeout.out request_timeout.c
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

// char req_header[] = "GET / HTTP/1.1\r\nUser-Agent:curl/7.19.7\r\nHost:127.0.0.1\r\nAccept: */*\r\n\r\n";
   char req_header[] = "GET / HTTP/1.1\r\nUser-Agent:curl/7.19.7\r\n";

int main(int argc, char* argv[])
{
        if (3 != argc)
        {
                printf("Usage: %s ip port\n", argv[0]);
                // ip   : 127.0.0.1
                // port : 80
                return -1;
        }
        const char* ip = argv[1];
        uint16_t port = atoi(argv[2]);

        struct sockaddr_in server_addr;

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(-1 != sockfd);

        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        int ret = inet_aton(ip, &server_addr.sin_addr);
        assert(-1 != ret);

        ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
        assert(-1 != ret);

        write(sockfd, req_header, strlen(req_header));
        close(sockfd);

        return 0;
}
