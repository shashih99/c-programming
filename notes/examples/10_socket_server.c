/* 10_socket_server.c - minimal TCP echo server (POSIX sockets)
 * Run:  ./server            (listens on 127.0.0.1:9090, serves ONE client, then exits)
 * Then in another terminal:  ./client "hello"     or:  nc 127.0.0.1 9090 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>       /* sockaddr_in, htons, inet_ntop */
#include <sys/socket.h>

#define PORT 9090

int main(void)
{
    /* 1. socket: create an endpoint (IPv4, TCP) */
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) { perror("socket"); return 1; }

    int yes = 1;             /* allow quick restart on the same port */
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    /* 2. bind: attach to an address + port */
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);                 /* host -> network byte order */
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);   /* 127.0.0.1 only */
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("bind"); return 1; }

    /* 3. listen: mark as passive, queue up to 5 pending connections */
    if (listen(server_fd, 5) == -1) { perror("listen"); return 1; }
    printf("server: listening on 127.0.0.1:%d\n", PORT);
    fflush(stdout);

    /* 4. accept: block until a client connects; returns a NEW socket for that client */
    struct sockaddr_in client = {0};
    socklen_t len = sizeof client;
    int client_fd = accept(server_fd, (struct sockaddr *)&client, &len);
    if (client_fd == -1) { perror("accept"); return 1; }
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, ip, sizeof ip);
    printf("server: client connected from %s:%d\n", ip, ntohs(client.sin_port));

    /* 5. recv / send: echo back in upper case */
    char buf[256];
    ssize_t n = recv(client_fd, buf, sizeof buf - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("server: received \"%s\"\n", buf);
        for (ssize_t i = 0; i < n; i++) buf[i] = toupper((unsigned char)buf[i]);
        send(client_fd, buf, n, 0);
    }

    /* 6. close both sockets */
    close(client_fd);
    close(server_fd);
    printf("server: done\n");
    return 0;
}
