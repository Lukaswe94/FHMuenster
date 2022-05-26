#include "Socket.h"
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int Bind(int socket, const struct sockaddr *address,
             socklen_t address_len){
                 if(bind(socket, address, address_len) != 0){
                     perror("bind");
                     return -1;
                 }
		 return 0;
             }
int Connect(int socket, const struct sockaddr *address, socklen_t address_len){
    if(connect(socket, address, address_len) != 0){
        perror("connect");
        return -1;
    }
    return 0;
}
int Socket(int __domain, int __type, int __protocol){
    int rv = socket(__domain, __type, __protocol);
    if(rv == -1){
        perror("socket");
        exit(-1);
    }
    return rv;
}

ssize_t Recvfrom(int __fd, void *__buf, size_t __n,
			int __flags, struct sockaddr * __addr,
			socklen_t *__addr_len){
                
                ssize_t rv = recvfrom(__fd,  __buf, __n, __flags,  __addr, __addr_len);
                if(rv == -1){
                    perror("recvfrom");
                    exit(-1);
                }
                return rv;
            }

ssize_t Sendto(int __fd, const void *__buf, size_t __n,
		       int __flags, const struct sockaddr * __addr,
		       socklen_t __addr_len){
                    ssize_t rv = sendto(__fd, __buf, __n, __flags, __addr, __addr_len);
                    if(rv == -1){
                        perror("sendto");
                        exit(-1);
                    }
                    return rv;
               }

ssize_t Recv(int fd, void *buf, size_t buflen, int flags) {
    ssize_t length = recv(fd, buf, buflen, flags);
    if (errno == EWOULDBLOCK || errno == EAGAIN) return -2;
    if (length == -1) {
        printf("Recv Fehler: %s\n", strerror(errno));
	exit(-1);
    }
    return length;
}

ssize_t Send(int fd, const void *buf, size_t buflen, int flags) {
    ssize_t length = send(fd, buf, buflen, flags);
    if (length == -1) {
        printf("Send Fehler: %s", strerror(errno));
    }
    return length;
}

int Shutdown(int fd, int how) {
    int return_value = shutdown(fd, how);
    if (return_value == -1) {
        printf("Shutdown Fehler: %s", strerror(errno));
    }
    return return_value;
}
int Listen(int fd, int backlog) {
    int return_value = listen(fd, backlog);
    if (return_value != 0) {
        perror("listen");
	exit(-1);
    }
    return return_value;
}

int Accept(int fd, struct sockaddr *addr, socklen_t *len) {
    int new_fd = accept(fd, addr, len);
    if (new_fd == -1) {
        printf("Accept Fehler: %s", strerror(errno));
    }
    return new_fd;
}

int Close(int fd) {
    int return_value = close(fd);
    if (return_value == -1) {
        printf("Close Fehler: %s", strerror(errno));
    }
    return return_value;
}
int Select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout){
	int rv =select(nfds, readfds, writefds, exceptfds, timeout);
	if(rv == -1){
		printf("Select Fehler: %s\n", strerror(errno));
		exit(-1);
	}
	return rv;
}
