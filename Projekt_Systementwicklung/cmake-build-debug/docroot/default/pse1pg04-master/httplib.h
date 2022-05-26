//
// Created by Sebastian Schinzel on 25.03.20.
//

#ifndef ECHO_SERVER_HTTPLIB_H
#define ECHO_SERVER_HTTPLIB_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DOC_ROOT "/home/pseuser/CLionProjects/pse1pg04/DocRoot"
#define EXTERN  "/home/pseuser/CLionProjects/pse1pg04/extern"
#define INTERN   "/home/pseuser/CLionProjects/pse1pg04/intern"

struct string {
    size_t len;
    size_t pos;
    char* str;
};
typedef struct string string;

string* str_cat(string* dest, const char* src,int len);
string* new_string(size_t );
void print_string(string* str);
string* cpy_str(const char* src, size_t len);
void free_str(string* str);
size_t get_length(string* str);
char* get_char_str(string* str);
void case_dont_matter( string* str,int from,int to);
void case_dont_matter_at_all(string* str);
string* rewrite(string* dest,char* new_str,int pos);

#endif //ECHO_SERVER_HTTPLIB_H