//
// Created by pseuser on 16.05.20.
//

#ifndef PSE_BASE64_H
#define PSE_BASE64_H
#include <openssl/sha.h>
#include <string.h>
#include "httplib.h"

void build_decoding_table1();
char *base64_encode(const unsigned char *data,size_t input_length, size_t *output_length);
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);
void base64_cleanup();
unsigned char * entschlusseln(unsigned char * data, size_t * out_len);
char * verschlusseln(unsigned char * data, size_t * out_len);
char * schickmachen(unsigned char * data, size_t * out_len);

#endif //PSE_BASE64_H
