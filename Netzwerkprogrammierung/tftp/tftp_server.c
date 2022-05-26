#include <errno.h>
#include <sys/socket.h>
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "Socket.h"
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include "cblib.h"
#include <stdbool.h>

#define TFTP_HDR_SIZE 4
#define BYTE 1
#define message_size(x) (x +4)
#define DATA_MAX 512
#define SOCKET_READ_TIMEOUT_SEC 1
#define BUFFER_SIZE (1<<16)
#define MAX_TIMEOUTS 3


typedef enum{
	RRQ=1,
	WRQ,
	DATA,
	ACK,
	ERROR
} opcode;

typedef enum{
	UNDEFINED,
	NOTFOUND,
	ACCESS,
	MEMORY,
	ILLEGALOP,
	TID,
	FILEEXIST,
	USER
} errorcode;

typedef struct{
	uint16_t opcode;
	char filename_mode[514];
} tftp_request;

typedef struct{
	uint16_t opcode;
	uint16_t block;
} tftp_ACK;

typedef struct{
	uint16_t opcode;
	uint16_t block;
	uint8_t data[512];
}tftp_data;

typedef struct{
	uint16_t opcode;
	uint16_t errorCode;
	char errormsg[512];
}tftp_error;

typedef struct{
	int fd;
	struct sockaddr_in6 addr;
	socklen_t addr_len;
	FILE *file;
	int file_size_in_blocks;
	uint16_t block;
	uint16_t last_acked;
	int last_read;
	bool is_ack;
	struct timer *timer;
	int retransmit_count;
} connector;

void teardown(connector *c){
	fclose(c->file);
	deregister_fd_callback(c->fd);
	stop_timer(c->timer);
	delete_timer(c->timer);
	Close(c->fd);

}
int get_file_size_in_blocks(FILE *file){
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	double result = (double) size / DATA_MAX;
	int rv = (int) ceil(result);
	return rv;
}
int int_pow(int base, int exp){
	int result = 1;
	while (exp) {
		if (exp % 2) result *= base;
		exp /= 2;
		base *= base;
	}
	return result;

}
int set_timeout(int rt_count){
	return int_pow(2, rt_count);
}

int tftp_send_data(connector *con){
	tftp_data *data = malloc(sizeof(tftp_data));
	data->block = htons(con->block);
	data->opcode = htons(DATA);
	int offset = (con->block-1) * DATA_MAX;
	fseek(con->file, offset, SEEK_SET);
	size_t retVal = fread(data->data, BYTE, DATA_MAX, con->file);
	Send(con->fd, (void *)data, message_size(retVal), 0);
	con->last_read = retVal;
	start_timer(con->timer, 10000);
	free(data);
	return retVal;
}

void tftp_send_ack(connector *c, uint16_t block){
	tftp_ACK *ack = malloc(sizeof(tftp_ACK));
	ack->opcode = htons(ACK);
	ack->block = htons(block);
	Send(c->fd, (void *) ack, sizeof(*ack), 0);
	start_timer(c->timer, 10000);
	free(ack);
}

void timeout_handling(void *con){
	connector *c = (connector *) con;
	if(c->retransmit_count >= MAX_TIMEOUTS){
		printf("Retransmission timeout limit reached. Terminating Connection\n");
		stop_timer(c->timer);
		delete_timer(c->timer);
		deregister_fd_callback(c->fd);
		Close(c->fd);
		free(c);
		return;
	}
	c->retransmit_count++;
	if(!c->is_ack){
		printf("Block %d: timeout #%d\n", c->block, c->retransmit_count);
		tftp_send_data(c);
	}
	else{
		printf("Ack %d: timeout #%d\n", c->block, c->retransmit_count);
		tftp_send_ack(c, c->block);
	}
}

void error_handling(int fd, char *err_str, uint16_t code){
	tftp_error *err = malloc(sizeof(tftp_error));
	err->opcode = htons(ERROR);
	err->errorCode = htons(code);
	strcpy(err->errormsg, err_str);
	Send(fd, (void *) err, sizeof(*err), 0);
	free(err);
	exit(-1);
}

void tftp_recv_ack(connector *con, uint16_t *opcode, uint16_t *block){
	tftp_ACK *ack = malloc(sizeof(tftp_ACK));
	ssize_t packetsize = Recv(con->fd, (void *) ack, sizeof(*ack), 0);
	if(packetsize < TFTP_HDR_SIZE){
		error_handling(con->fd, "Wrong format", UNDEFINED);
	}
	*opcode = ntohs(ack->opcode);
	*block = ntohs(ack->block);
	free(ack);
}

void tftp_handle_write(void *con){
	connector *c = (connector *) con;
	int connfd = c->fd;
	tftp_data *data = malloc(sizeof(tftp_data));
	size_t packetsize = Recv(connfd, (void *) data, sizeof(tftp_data), 0);
	if(packetsize < TFTP_HDR_SIZE){
		error_handling(connfd, "Wrong format", UNDEFINED);
	}
	printf("Received block: %d\n", ntohs(data->block));
	printf("Size: %ld\n", packetsize);

	if(ntohs(data->opcode) == DATA){
		if(c->block == ntohs(data->block)){
			fwrite(data->data, 1, packetsize-TFTP_HDR_SIZE, c->file);
			c->block++;
		}
		tftp_send_ack(c, ntohs(data->block));
		free(data);
	}
	else{
		error_handling(connfd, "Invalid opcode", 4);
	}
	if(packetsize < DATA_MAX + TFTP_HDR_SIZE){
		teardown(c);
	}
}

void tftp_handle_read(void *con){
	connector *c = (connector *) con;
	uint16_t ack_opcode, ack_block = 0;

	tftp_recv_ack(c, &ack_opcode, &ack_block);
	if(ack_block >= c->file_size_in_blocks && c->last_read < DATA_MAX){
		teardown(c);
		return;
	}
	c->block = ack_block+1;
	c->retransmit_count = 0;
	printf("current block: %d\n", c->block);
	tftp_send_data(c);
	printf("sending :%d bytes\n", c->last_read);
}

void tftp_connection_init(void *s){
	int v6_only = 0;
	int reuse_addr = 1;
	tftp_request *req = malloc(sizeof(tftp_request));
	struct sockaddr_in6 server_addr;

	connector *c;
	c = malloc(sizeof(connector));
	c->file = malloc(sizeof(FILE));
	memset((void *)&c->addr, 0, sizeof(c->addr));
	c->addr_len = sizeof(struct sockaddr_in6);

	int fd = *(int *) s;
	int connfd = Socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	setsockopt(connfd, IPPROTO_IPV6, IPV6_V6ONLY,(const void *) &v6_only , sizeof(int));
	setsockopt(connfd, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse_addr, sizeof(reuse_addr));

	srand(time(NULL));
	memset((void *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
#ifdef HAVE_SIN_LEN
	server_addr.sin6_len = sizeof(struct sockaddr_in6);
#endif
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = rand() % ((1<<16) +1 -1024) +1024;
	ssize_t size = Recvfrom(fd, (void *) req, sizeof(req), 0, (struct sockaddr *)&c->addr, &c->addr_len);
	if(size < TFTP_HDR_SIZE){
		error_handling(fd, "Wrong format", UNDEFINED);
	} 
	printf("Binding to new Port: %d\n", server_addr.sin6_port);
	Bind(connfd, (const struct sockaddr *) &server_addr, (socklen_t)sizeof(server_addr));

	int con = Connect(connfd,(const struct sockaddr *) &c->addr, c->addr_len);
	if(con == -1) {
		teardown(c);
		return;
	}
	c->fd = connfd;
	if(memchr(req->filename_mode, '\0', size - 2) == NULL){
		error_handling(connfd, "Wrong format", UNDEFINED);
	}
	char *filename = &req->filename_mode[0];

	char *mode = &req->filename_mode[strlen(filename)+1];

	if(memchr(mode, '\0', size - 2 - strlen(filename)) == NULL){
		error_handling(connfd, "Wrong format", UNDEFINED);	
	} 

	if(strstr(mode, "octet") == NULL){ 
		error_handling(connfd, "Only octet supported" , UNDEFINED);
	}
	c->timer = create_timer(timeout_handling, (void *)c, "Timer");
	c->retransmit_count = 0;
	c->last_acked = -1;

	int op = ntohs(req->opcode);
	if(op == WRQ){
		c->file = fopen(filename, "w+");
		tftp_send_ack(c, 0);
		start_timer(c->timer, 10000);
		c->block = 1;
		c->is_ack = true;
		register_fd_callback(c->fd, tftp_handle_write, (void *) c);
	}

	else if(op ==RRQ){
		c->file = fopen(filename, "r");
		if(c->file == NULL){
			error_handling(connfd, "File not found", NOTFOUND);
		}
		c->file_size_in_blocks = get_file_size_in_blocks(c->file);
		c->block = 1;
		c->is_ack = false;
		tftp_send_data(c);
		printf("current block: %d\n", c->block);
		printf("sending: %d bytes\n", c->last_read);
		start_timer(c->timer, 10000);
		register_fd_callback(c->fd, tftp_handle_read, (void *) c);
	}
	else 
		error_handling(c->fd, "Unsupported Opcode", ILLEGALOP);
}

int main(void)
{	
	init_cblib();
	struct sockaddr_in6 server_addr;
	int fd;
	int v6_val = 0;
	int reuse_addr = 1;
	fd = Socket(AF_INET6,SOCK_DGRAM , IPPROTO_UDP);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&reuse_addr, sizeof(int));
	setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY,(const void *) &v6_val , sizeof(int));
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
#ifdef HAVE_SIN_LEN
	server_addr.sin6_len = sizeof(struct sockaddr_in6);
#endif
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons(4444);
	Bind(fd, (const struct sockaddr *) &server_addr, (socklen_t)sizeof(server_addr));
	printf("Bind succesful\n");
	register_fd_callback(fd, tftp_connection_init, (void *)&fd);
	handle_events();
	Close(fd);


	return (0);
}
