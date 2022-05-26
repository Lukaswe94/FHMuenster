//
// Created by pseuser on 16.06.20.
//

#ifndef PSE_REQUEST_HANDELING_H
#define PSE_REQUEST_HANDELING_H
#include "authentication_handeling.h"
#include "httplib.h"
#include "base64.h"
#include "error_handeling.h"
#include "file_handeling.h"
#include "authentication_handeling.h"
#include "request_handeling.h"

string *get_host(string *request);
string *get_part(string *str, size_t start_position);

#endif //PSE_REQUEST_HANDELING_H
