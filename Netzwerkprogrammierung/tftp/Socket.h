#ifndef UDP_EXAMPLES_SOCKET_H
#define UDP_EXAMPLES_SOCKET_H
#include <sys/select.h>
#include <sys/socket.h>

int Bind(int socket, const struct sockaddr *address,
            socklen_t address_len);

int Connect(int socket, const struct sockaddr *address, socklen_t address_len);

int Socket(int __domain, int __type, int __protocol);

ssize_t Recvfrom (int __fd, void *__buf, size_t __n,
			int __flags, struct sockaddr * __addr,
			socklen_t * __addr_len);

ssize_t Sendto (int __fd, const void *__buf, size_t __n,
		       int __flags, const struct sockaddr * __addr,
		       socklen_t __addr_len);
ssize_t Recv(int fd, void *buf, size_t buflen, int flags);
ssize_t Send(int fd, const void *buf, size_t buflen, int flags);
int Shutdown(int fd, int how);
int Listen(int fd, int backlog);
int Accept(int fd, struct sockaddr *addr, socklen_t *len);
int Close(int fd);
int Select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);

#endif //UDP_EXAMPLES_SOCKET_H
