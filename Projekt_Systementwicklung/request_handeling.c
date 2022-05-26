//
// Created by pseuser on 16.06.20.
//

#include "request_handeling.h"
/**
 * Nimmt die eingehende Request an und liest aus diese den Host aus
 * gibt NULL turück wenn keiner vorhanden ist
 * @param string *: request
 * @author pse1pg03
 * @return string*: Host der request
 */
string *get_host(string *request) {
    char *position = NULL;
    char *ende = NULL;
    char *EndOfHeader = "\r\n\r\n";
    string *host;
    int counter=0;
    int bool=0;
    for(counter;counter<(request->pos)-1;counter++) {
        if (request->str[counter]=='\r')
        bool=1;
    }

    if(bool==0)
        return NULL;
    counter=0;
    position = memchr(request->str, 13, request->pos);//13 = Carriage Return
    if(position ==  NULL)
        return NULL;
    else {
        while ((*(position + 2) != 'h') && (*(position + 2) != 'H')) { //falls nach dem ersten \r kein host befinden sollte wird ab dem nächsten gesucht
            if( memcmp(position, EndOfHeader, 4) == 0){
                return NULL;
            }
            position = memchr(position + 2, 13, request->pos);

        }  // hier position = \r Das ist direkt vor der Zeile mit "host"

        while (*position != ':') {
            position++;
            counter++;
        }
        if (counter !=6) {
            return NULL;
        }
        position++;
        while (*position == ' ')
            position++;
        ende = position;
        while (*ende != ':' && *ende != '\r')
            ende++;
        host = cpy_str(position, ende - position); // Kopieren des parts (methode, resource, protocol)
        host->pos = ende - position - 1;

        return host;
    }
}

/**
 * Funktion die aus der Headline die jeweiligen Parts ausließt
 * @param string*: str, die request
 * @param size_t: start_position die Position an der begonnen wird zu suchen
 * @author pse1pg03
 * @return string *: Methode/resource/protocol
 */
string *get_part(string *str, size_t start_position) {
    int i;
    string *dest;

    if (str->str[start_position] == '\n' || str->str[start_position] == '\r' || str->str[start_position] == ' ') {
        return NULL;
    }
    for (i = start_position; str->str[i] != ' ' && str->str[i] != '\r'; i++) {
        if ( i >= PATH_MAX)
            return NULL;
    } // Die Länge der ersten Zeile ermitteln



    dest = cpy_str(str->str + start_position, i - start_position); // Kopieren des parts (methode, resource, protocol)

    dest->pos = i - start_position - 1;

    return dest;
}