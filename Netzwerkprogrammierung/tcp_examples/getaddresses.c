#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[]) {
    struct addrinfo *results, *result;
    int error = 0;
    struct addrinfo addrHints;

    if(argc < 2){
        printf("Please enter Domain to resolve:");
        exit(-1);
    }

    bzero(&addrHints, sizeof(addrHints));
	//    addrHints.ai_socktype = SOCK_STREAM;
    addrHints.ai_family = AF_UNSPEC;
    error = getaddrinfo(argv[1], NULL, &addrHints, &results);
    if(error == 0){
        for (result = results; result != NULL; result = result->ai_next) {
            char hostname[NI_MAXHOST] = "";
            error = getnameinfo(result->ai_addr, result->ai_addrlen, hostname, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if(error == 0){
                printf("%s\n", hostname);
            }else{
                fprintf(stderr,"Error getnameinfo %s\n", gai_strerror(error));
            }

        }
        freeaddrinfo(results);
    }else{
        fprintf(stderr," Error getaddrinfo %s\n", gai_strerror(error));
    }
}

