/*-
 * Copyright (c) 2013 Michael Tuexen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <netdb.h>
#include "../udp_examples/Socket.h"

#define BUFFER_SIZE  (1<<16)
#define MESSAGE_SIZE (9216)

int main(int argc, char **argv)
{
	int fd, s;
	fd_set readfds;
	ssize_t len;
	char buf[BUFFER_SIZE];
	bool fd_stdin = true;
	struct addrinfo hints;
	struct addrinfo *res, *pptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = 0;
	hints.ai_protocol = IPPROTO_TCP;          
	s = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	for (pptr = res; pptr != NULL; pptr = pptr->ai_next) {
		fd = Socket(pptr->ai_family, pptr->ai_socktype, pptr->ai_protocol);
		if (connect(fd, pptr->ai_addr, pptr->ai_addrlen) != -1){
			printf("connected..\n");
			break;                  	
		}
		printf("no connection\n");
		Close(fd);
	}

	if (pptr == NULL) {               
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(res);

	for(;;){
		memset(buf, 0, sizeof(buf));
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);
		FD_SET(0, &readfds);
		Select(fd+1, &readfds, NULL, NULL, NULL);
		if( FD_ISSET(0, &readfds) && fd_stdin){
			len= read(0, (void *) buf, sizeof(buf));
			if(len == 0){
				Shutdown(fd, SHUT_WR);
				fd_stdin = false;
			}
			else if(len == -1){
				printf("Fehler read: %s\n", strerror(errno));
			}
			else{
				Send(fd, (const void *)buf, len, 0);
			}
		}
		if(FD_ISSET(fd, &readfds)){
			memset(buf, 0, sizeof(buf));
			len = Recv(fd, (void *)buf, sizeof(buf), 0);
			if(len == 0 && !fd_stdin){
				printf("Verbindungsabbau..\n");
				break;
			}
			ssize_t rv = write(1, (const void *)buf, (size_t)len);
			if(rv == -1){
				printf("Write Fehler: %s\n", strerror(errno));
			}
		}
	}

	Close(fd);

	return (0);
}
