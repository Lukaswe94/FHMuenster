#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../udp_examples/Socket.h"

#define BUFFER_SIZE (1<<16)

void *char_generator(void *arg) {
    int fd = *((int *) arg);
    free(arg);
    printf("Neuer Thread für den Dateideskriptor %d wurde gestartet!\n", fd);
    fd_set read_fd_set, write_fd_set;
    char buf[BUFFER_SIZE];

    while (1) {
        FD_ZERO(&read_fd_set);
        FD_ZERO(&write_fd_set);

        FD_SET(fd, &read_fd_set);
        FD_SET(fd, &write_fd_set);

        Select(FD_SETSIZE, &read_fd_set, &write_fd_set, NULL, NULL);

        // Falls 0 Bytes empfangen werden soll die Verbindung beendet werden
        if(FD_ISSET(fd, &read_fd_set) && Recv(fd, buf, BUFFER_SIZE, 0) == 0) {
            printf("Verbindungsabbau von Dateideskriptor %d...\n", fd);
            break;
        }

        if(FD_ISSET(fd, &write_fd_set)) {
            memset(buf, 0, sizeof(buf));
            int chars = 99;
            int i;
            for (i = 0; i < chars; i++) {
                buf[i] = (i % 94) + ' '; // 94 printable ASCII chars
            }
            buf[99] = '\n';
            chars++;
            ssize_t sent = 0;
            while (sent < chars) {
                sent += Send(fd, buf + sent, chars - sent, 0);
            }
        }
        sleep(1);
    }
    Close(fd);
    return NULL;
}

int main(void) {
    int fd;
    struct sockaddr_in server_addr;
    fd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
#ifdef HAVE_SIN_LEN
    server_addr.sin_len = sizeof(struct sockaddr_in);
#endif
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(3456);

    Bind(fd, (const struct sockaddr *) &server_addr, (socklen_t)
    sizeof(server_addr));

    Listen(fd, 3);

    while (1) {
        int *new_fd = malloc(sizeof(int));
        *new_fd = Accept(fd, NULL, NULL);
        pthread_t tid;
        if (pthread_create(&tid, NULL, char_generator, new_fd) == -1) {
            printf("pthread_create Fehler: %s", strerror(errno));
        }
        if (pthread_detach(tid)) {
            printf("pthread_detach Fehler: %s", strerror(errno));
        }
    }
    Close(fd);
}