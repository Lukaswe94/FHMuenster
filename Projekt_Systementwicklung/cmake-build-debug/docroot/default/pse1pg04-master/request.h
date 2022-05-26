//
// Created by pseuser on 08.05.20.
//

#ifndef PSE1PG04_REQUEST_H
#define PSE1PG04_REQUEST_H

void get_uri(string *tmp, const string *request);
string *uri_decoder(const string *request);
string* request_bereinigen(string* req);
string* request_leerzeichen_weg(string* req);
char* getHost(string* request);
int testGet(string* req,char * host);
int test(char* test, char * host);
#endif //PSE1PG04_REQUEST_H
