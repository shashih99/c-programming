/* 10_socket_client.c - minimal TCP client for 10_socket_server.c
 * Run:  ./client "some text"   (server must already be running) */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090

int main(int argc, char *argv[])
{
    const char *msg = argc > 1 ? argv[1] : "hello, server";

    int fd = socket(AF_INET, SOCK_STREAM, 0);                 /* 1. socket  */
    if (fd == -1) { perror("socket"); return 1; }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);          /* text -> binary address */

    if (connect(fd, (struct sockaddr *)&addr, sizeof addr) == -1) {   /* 2. connect */
        perror("connect");
        close(fd);
        return 1;
    }

    send(fd, msg, strlen(msg), 0);                             /* 3. send */
    char buf[256];
    ssize_t n = recv(fd, buf, sizeof buf - 1, 0);              /* 4. recv */
    if (n > 0) {
        buf[n] = '\0';
        printf("client: sent \"%s\", got back \"%s\"\n", msg, buf);
    }
    close(fd);                                                 /* 5. close */
    return 0;
}
