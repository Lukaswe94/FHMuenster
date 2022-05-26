#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../udp_examples/Socket.h"

#define BUFFER_SIZE (1<<16)
#define MAX_CLIENTS 10


int main(int argc, char **argv) {
    int clients[MAX_CLIENTS];
    ssize_t len;
    int fd, port, maxfd = 0, ClientFD = 0;
    char buf[BUFFER_SIZE];
    fd_set read_fd_set;
    int val = 1;
    int nonval = 0;

    if (argc != 2) {
        port = 3333; //Default Port
    }else{
        port =  atoi(argv[1]);
    }

    printf("Discard Server lauft auf Port: %d",port);
    for (int i = 0; i < MAX_CLIENTS; i++) {
      clients[i] = -1;
    }
    fd = Socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &val, sizeof(int));
    setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&nonval, sizeof(nonval));		
    struct sockaddr_in6 server_addr;
    memset((void *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
#ifdef HAVE_SIN_LEN
    server_addr.sin6_len = sizeof(struct sockaddr_in6);
#endif
    server_addr.sin6_addr = in6addr_any;
    server_addr.sin6_port = htons(port);

    Bind(fd, (const struct sockaddr *) &server_addr, sizeof(server_addr));
    Listen(fd, 10); // Hör auf gebindeten FD backlog 10 Pending Verbindungen (Backlog)
    maxfd = fd;
    //Serverloop
    while (1){
        FD_ZERO(&read_fd_set);
        FD_SET(fd, &read_fd_set);

        for (int i = 0; i < MAX_CLIENTS; i++){
            if (clients[i] >=0){
                FD_SET(clients[i], &read_fd_set); //Füge verbundene Clients zum Read Set hinzu
            }
        }


        Select(maxfd+1, &read_fd_set, NULL, NULL, NULL);

        if (FD_ISSET(fd, &read_fd_set)) { // Neue Anfrage verfügbar ?
            ClientFD = Accept(fd, NULL, NULL); //Verbindung annehmen
            int i;
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == -1) {
                    clients[i] = ClientFD; // Speicher neuen FD in ARRAY der Clients
                    if(ClientFD > maxfd){
                        maxfd = ClientFD;
                    }
                    break;
                }
            }
            if (i == MAX_CLIENTS) { //Verbindung schliessen wenn Max CLients verbunden sind
                printf("Connection derzeit nicht möglich.");
                Close(ClientFD);
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
           if (clients[i] >= 0 && FD_ISSET(clients[i], &read_fd_set)) { //Sockt ist Lesbar
                len = Recv(clients[i], buf, BUFFER_SIZE, 0); //Nachricht von Socket lesen
                if (len != 0) {
                    write(1,buf,len);
                    memset(buf, 0, BUFFER_SIZE); //Nachricht verwerfen
                } else {
                    Close(clients[i]);
                    printf("Connection geschlossen.");
                    clients[i] = -1;
                    maxfd = fd;
                    for(int j=0; j < MAX_CLIENTS; j++)
                    {
                        if (clients[j] > maxfd)
                            maxfd = ClientFD;
                    }

                }
            }
        }

    }

    return 0;
}

