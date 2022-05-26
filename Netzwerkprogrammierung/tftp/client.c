//
// Created by bh860403 on 1/1/22.
//
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include "Socket.h"
#include "cblib.h"

#define BUFFER_SIZE 512
#define TIMEOUT 20000
#define MAXTIMEOUTS 3
#define MAX_USER_INPUT_LEN PATH_MAX + 4
#define PATH_MAX 30
#define MODE "octet"
#define TFTP_HEADER_SIZE 4

typedef struct{
    uint16_t opcode;
    uint16_t block;
    uint8_t data[512];
}tftpData;
typedef enum{
    RRQ=1,
    WRQ =2,
    DATA=3,
    ACK=4,
    ERROR=5
} opcode;
struct tftpSession{
    int sockFd;
    struct sockaddr_in6 addr;
    socklen_t addr_len;
    FILE *localFilePointer;
    int block;
    int lastBlockSended;
    char buf[BUFFER_SIZE+TFTP_HEADER_SIZE];
    int  buf_len;
    struct timer * timer;
    int timeOutCounter;
};
typedef struct{
    uint16_t opcode;
    uint16_t errorCode;
    char errormsg[512];
}tftp_error;
typedef struct{
    uint16_t opcode;
    uint16_t block;
} tftpAck;

void error_handling(struct tftpSession * session, char *err_str, uint16_t code);
int sendRequestToServer(int opCode, char * filePath, struct tftpSession * client);
char * getFilePath(const char * userInput);
int sendAck(struct tftpSession * server);
int sendData(struct tftpSession* session);
int int_pow(int base, int exp);
void timeout(void *args);
void commandLine(void *args);
void closeSession(struct tftpSession* session);
void getCommand(struct tftpSession* session);
void putCommand(struct tftpSession* session);
/* Main Function*/
int main(int argc, char **argv) {

    int fd;
    struct tftpSession client;
    struct addrinfo *results, *result;
    struct addrinfo hints;

    if(argc != 3){
        fprintf(stderr,"Bitte Host und Port übergeben.");
        exit(-1);
    }

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    if(0 < getaddrinfo(argv[1], argv[2], &hints , &results)) {
        fprintf(stderr,"Adresse konnte nicht aufgelöst werden.");
        exit(-1);
    }else{
        /* getaddrinfo() returns a list of adress structures try to connect to one*/
        for (result = results; result != NULL; result = result->ai_next) {
            fd = Socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            if(fd > 0){
                if (Connect(fd, result->ai_addr, result->ai_addrlen) == 0)
                    break;
            }

            Close(fd);
        }
        close(fd);
        // Create requiered Socket
        if(result->ai_family == AF_INET){
            fd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        } else if (result->ai_family == AF_INET6) {
            fd = Socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
        }else{
            exit(EXIT_FAILURE);
        }

    }

    bzero(&client, sizeof(struct tftpSession));
    client.sockFd = fd;
    client.addr = *((struct sockaddr_in6*)result->ai_addr);
    client.addr_len = result->ai_addrlen;

    printf("<tftp> ");
    fflush(stdout);

    init_cblib();
    register_stdin_callback(&commandLine, (void*)&client);
    handle_events();

    Close(fd);
    freeaddrinfo(results);
    return -1;
}
/* Parse Filepath from User input */
char * getFilePath(const char * userInput){
    // First 3 Command => " " => "Filepath"
    if(userInput[3] != ' '){
        return NULL;
    }
    int i = 3;
    do {
        i +=1;
    } while (userInput[i] != '\n' && userInput[i] != '\0');
    char * path = calloc(sizeof(char)*i,1);
    for (int  j = 4; j < i; ++j) {
        path[j-4] = userInput[j];
    }
    path[i+1] = '\n';
    return path;
}
/* Send ACK to a server */
int sendAck(struct tftpSession * server){
    tftpAck  *ack = malloc(sizeof(tftpAck));
    ack->opcode = htons(ACK);
    ack->block = htons(server->block);
   int rv = Sendto(server->sockFd, (void *) ack, sizeof(ack), 0, (struct sockaddr*)&server->addr, server->addr_len);
    memcpy(server->buf,ack, sizeof(ack));
    server->buf_len = rv;
    server->timeOutCounter = 0;
    stop_timer(server->timer);
    start_timer(server->timer,TIMEOUT);

    free(ack);
}
/* Send RRQ/WRQ Request to tftp server */
int sendRequestToServer(int opCode, char * filePath, struct tftpSession * client){
    char * p;
    *(short *) client->buf = htons(opCode);
    p = client->buf +2;
    strcpy(p, filePath);
    p += strlen(filePath) + 1;
    strcpy(p , MODE);
    p += strlen(MODE) + 1;
    int rv = Sendto(client->sockFd, client->buf, p - client->buf, 0,
                    (struct sockaddr *)&client->addr, sizeof client->addr);
    client->buf_len = rv;
    client->timeOutCounter = 0;
    return 0;
}
/* Handle the Commandline (Callback STDIN) */
void commandLine(void *args){
    struct tftpSession *client = malloc(sizeof(struct tftpSession));
    if(client){
        memcpy(client, args, sizeof(struct tftpSession));
    }else{
        fprintf(stderr,"Fehler MALLOC");
        exit(-1);
    }

    char user_input[MAX_USER_INPUT_LEN];
    ssize_t user_input_len = -1;

    int fd;
    // create Connection Socket
    if(client->addr.sin6_family == AF_INET){
        fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    } else if (client->addr.sin6_family == AF_INET6) {
        fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    }else{
        exit(EXIT_FAILURE);
    }

    client->sockFd = fd;

    user_input_len = read(STDIN_FILENO, user_input, MAX_USER_INPUT_LEN);
    if (user_input_len < 0)
        return;

    if (!strncmp(user_input, "q\n", 2))
        exit(0);

    if (!strncmp(user_input, "get", 3)) {
        // 1. Create the File
        char * filePath = getFilePath(user_input);
        client->localFilePointer = fopen(filePath, "w");

        if(!client->localFilePointer){
            fprintf(stderr,"Fehler beim öffnen der Datei %s",filePath);
            return;
        }

        // 2. Send the RRQ
        sendRequestToServer(RRQ, filePath, client);

        // 3. Collect the Data
        register_fd_callback(client->sockFd, getCommand, client);

        client->timer = create_timer(&timeout,client,"get");

        start_timer(client->timer,TIMEOUT);
        return;

    }
    if (!strncmp(user_input, "put", 3)) {
        // 1. Open the File
        char * filePath = getFilePath(user_input);
        client->localFilePointer = fopen(filePath, "r");

        if(!client->localFilePointer){
            fprintf(stderr,"Fehler beim öffnen der Datei %s",filePath);
            return;
        }


        // 2. Send the WRQ
        sendRequestToServer(WRQ, filePath, client);


        // 4. Collect the Data
        register_fd_callback(client->sockFd, putCommand, client);

        client->timer = create_timer(&timeout,client,"put");
        start_timer(client->timer,TIMEOUT);
        return;
    }

    fprintf(stderr, "Ungültiger Befehl bitte erneut besuchen.\n");

    printf("<tftp_client> ");
    fflush(stdout);
}
/* Manage the connection timeout */
void timeout(void *args){
    struct tftpSession* server = (struct tftpSession*) args;
    if(server->timer){
        fprintf(stderr,"Timeout\n");
        sendto(server->sockFd, server->buf, server->buf_len, 0, (struct sockaddr*)&server->addr, server->addr_len);

        if(server->timeOutCounter++ > MAXTIMEOUTS){
            error_handling(server,"Retransmission timeout reached!",0);
            return;
        }
        // Restart Timer
        start_timer(server->timer,TIMEOUT* int_pow(2,server->timeOutCounter));
    }
}
/*Send Data to the Server*/
int sendData(struct tftpSession * session){
    session->block++; // last block acked => increase blocknumber
    tftpData * packetBuffer = malloc(sizeof(tftpData));
    packetBuffer->block = session->block;
    packetBuffer->opcode = DATA;
    //Read from File
    int rv = (int) fread(packetBuffer->data, 1, BUFFER_SIZE, session->localFilePointer);
    char * sendBuffer = calloc(16+rv,1);
    *(short *) sendBuffer = htons(DATA);
    char * p = sendBuffer +2;
    *(short *) p = htons(session->block);
    p = p+2;
    memccpy(p,packetBuffer->data,sizeof(char ),rv);
    int count = sendto(session->sockFd, sendBuffer, 16 + rv, 0, (struct sockaddr *)&session->addr, session->addr_len);
    memcpy(session->buf, sendBuffer, count);
    session->buf_len = count;
    session->timeOutCounter = 0;
    stop_timer(session->timer);
    start_timer(session->timer, TIMEOUT);
    return count;
}
/* Get Command*/
void getCommand(struct tftpSession * session){

    char buffer[BUFFER_SIZE + TFTP_HEADER_SIZE];

    int count = recvfrom(session->sockFd, buffer, BUFFER_SIZE + TFTP_HEADER_SIZE, 0, (struct sockaddr *) &session->addr,
                         &session->addr_len);

    if(count >= 4) {
        if (ntohs(*(short *) buffer) == ERROR) {
            fprintf(stderr, "Fehler: %s\n", buffer + 4);
        } else {
            printf("Received %d Bytes from SERVER.\n", count);

            uint16_t *opCode = (uint16_t *) buffer;
            uint16_t *blockNumber = (uint16_t *) buffer + 1;

            if (htons(*opCode) == DATA) {
                if (htons(*blockNumber) == session->block + 1) {
                    printf("Received Block[%d]\n", htons(*blockNumber));
                    // Next write the Data to the File
                    if (count != TFTP_HEADER_SIZE) {
                        if (fwrite(buffer + 4, sizeof(char), count - TFTP_HEADER_SIZE, session->localFilePointer) ==
                            0) {
                            error_handling(session, "Error writing File.", 0);
                            return;
                        }
                        session->block++;
                        sendAck(session);
                    }
                    if (BUFFER_SIZE > count - TFTP_HEADER_SIZE) {
                        printf("Reciving Lastblock[%d] finished.\n", session->block);
                        // Clear the client now
                        deregister_fd_callback(session->sockFd);
                        closeSession(session);
                        return;
                    }

                }

            } else {
                error_handling(session, "Unexpected Package", 0);
            }
        }
    }else{
        error_handling(session, "Wrong Package Size",0);
    }
}
/* Put Command*/
void putCommand(struct tftpSession * session){
    char buffer[BUFFER_SIZE + TFTP_HEADER_SIZE];

    int count = recvfrom(session->sockFd, buffer, BUFFER_SIZE + TFTP_HEADER_SIZE, 0, (struct sockaddr *) &session->addr,
                     &session->addr_len);

    if(count >= 4) {
        if (ntohs(*(short *) buffer) == ERROR) {
            fprintf(stderr, "Fehler: %s\n", buffer + 4);
        } else {
            printf("Received %d Bytes from SERVER.\n", count);

            uint16_t *opCode = (uint16_t *) buffer;
            uint16_t *blockNumber = (uint16_t *) buffer + 1;

            if (htons(*opCode) == ACK) {
                if (htons(*blockNumber) == session->block) {
                    printf("Received Ack for Block[%d]\n", htons(*blockNumber));

                    if (session->lastBlockSended) {
                        printf("Last Package ACKED by the Server\n");
                        closeSession(session);
                        return;
                    }
                    if (sendData(session) < 516) {
                        printf("Last Package sended\n");
                        session->lastBlockSended = 1;
                    } else {
                        session->lastBlockSended = 0;
                    }
                }

            } else {
                error_handling(session, "Unexpected Package", 0);
            }

        }
    }else{
        error_handling(session,"Wrong Package Size",0);
    }

}
/* Clear Session*/
void closeSession(struct tftpSession* session){

    deregister_fd_callback(session->sockFd);

    stop_timer(session->timer);
    delete_timer(session->timer);
    session->timer = NULL;

    if(session->localFilePointer != NULL)
        fclose(session->localFilePointer);

    free(session);

    session = NULL;
    printf("Session gelöscht !\n");
    printf("<tftp> ");
    fflush(stdout);
}
/* Handle Errors*/
void error_handling(struct tftpSession * session, char *err_str, uint16_t code){
    tftp_error *err = malloc(sizeof(tftp_error));
    err->opcode = htons(ERROR);
    err->errorCode = htons(code);
    strcpy(err->errormsg, err_str);
    Sendto(session->sockFd, err, sizeof (tftp_error), 0, (struct sockaddr*)&session->addr, session->addr_len);
    free(err);
    closeSession(session);
}
/* Pow Helpfunction for the Timeout calculation*/
int int_pow(int base, int exp){
    int result = 1;
    while (exp) {
        if (exp % 2) result *= base;
        exp /= 2;
        base *= base;
    }
    return result;

}
