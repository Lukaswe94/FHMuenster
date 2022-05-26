//
// Created by pseuser on 16.06.20.
//

#ifndef PSE_AUTHENTICATION_HANDELING_H
#define PSE_AUTHENTICATION_HANDELING_H

#include "httplib.h"
#include "base64.h"
#include "error_handeling.h"
#include "file_handeling.h"
#include "authentication_handeling.h"
#include "request_handeling.h"


char*    getRequestAuthorization(const string *request);
string * getPw(char * data);
void B_P_ausgabe(char* B_P);
int      pswd_vergleich(char* passwort,char* dateipfad);

#endif //PSE_AUTHENTICATION_HANDELING_H
