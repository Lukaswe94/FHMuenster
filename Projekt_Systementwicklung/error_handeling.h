//
// Created by pseuser on 16.06.20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include "httplib.h"
#include "base64.h"





#ifndef PSE_ERROR_HANDELING_H
#define PSE_ERROR_HANDELING_H

int      get_status_code(char* ress, char* meth, char* host, char * protocol,char* DOC_ROOT_INTERN, char* DOC_ROOT_EXTERN,char* DOC_ROOT_DEFAULT,char *startDir,char* dateipfad);
string*  statcode_to_string (string* erstelinie, string* cntlen, string* body, const char * char_const );

#endif //PSE_ERROR_HANDELING_H
