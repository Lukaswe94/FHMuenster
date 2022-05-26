#include "socket.h"

int Socket(int family, int type, int protocol) {
    int fd = socket(family, type, protocol);
    if (fd == -1) {
        printf("Socket Fehler: %s", strerror(errno));
    }
    return fd;
}

int Connect(int fd, const struct sockaddr *addr, socklen_t len) {
    int return_value = connect(fd, addr, len);
    if (return_value == -1) {
        printf("Connect Fehler: %s", strerror(errno));
    }
    return return_value;
}

int Close(int fd) {
    int return_value = close(fd);
    if (return_value == -1) {
        printf("Close Fehler: %s", strerror(errno));
    }
    return return_value;
}

int Bind(int fd, const struct sockaddr *addr, socklen_t addrlen) {
    int return_value = bind(fd, addr, addrlen);
    if (return_value == -1) {
        printf("Bind Fehler: %s", strerror(errno));
    }
    return return_value;
}

int Listen(int fd, int backlog) {
    int return_value = listen(fd, backlog);
    if (return_value == -1) {
        printf("Listen Fehler: %s", strerror(errno));
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

ssize_t Recvfrom(int fd, void *buf, size_t buflen, int flags, struct sockaddr *from, socklen_t *addrlen) {
    ssize_t length = recvfrom(fd, buf, buflen, flags, from, addrlen);
    if (length == -1) {
        printf("Recvfrom Fehler: %s", strerror(errno));
    }
    return length;
}

ssize_t Sendto(int fd, void *buf, size_t buflen, int flags, const struct sockaddr *to, socklen_t addrlen) {
    ssize_t length = sendto(fd, buf, buflen, flags, to, addrlen);
    if (length == -1) {
        printf("Sendto Fehler: %s", strerror(errno));
    }
    return length;
}

ssize_t Recv(int fd, void *buf, size_t buflen, int flags) {
    ssize_t length = recv(fd, buf, buflen, flags);
    if (length == -1) {
        printf("Recv Fehler: %s", strerror(errno));
    }
    return length;
}

ssize_t Send(int fd, void *buf, size_t buflen, int flags) {
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