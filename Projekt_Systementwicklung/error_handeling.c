//
// Created by pseuser on 16.06.20.
//

#include "error_handeling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "httplib.h">
#include <unistd.h>
/**
 * Die Funktion bekommt die Resrouce, die Methode, das Protocoll und den Host-Wert der Request. Sie wertet diese aus, und gibt entsprechend
 * einen Status_code zurück.
 * @param char *: ress, die angegebene Resource bei der Request
 * @param char *: meth, die verwendete Methode bei der Request
 * @param char *: host, der Hostname bei der Request
 * @param char *: DOC_ROOT_INTERN/DOC_ROOT_EXTERN/DOC_ROOT_DEFAULT
 * @param char *: startDir, die docRoot zu dem Verzeichniss der Datei
 * @param char *: dateipfad, dateipfad von htpasswd
 * @author pse1pg03 und verfeinert durch pse1pg04
 * @return int: Status code
 */
int get_status_code(char *ress, char *meth, char *host, char * protocol,char* DOC_ROOT_INTERN, char* DOC_ROOT_EXTERN,char* DOC_ROOT_DEFAULT,char *startDir,char* dateipfad) {
    const char *localhost = "localhost";
    const char *localnb = "127.0.0.1";
    const char *intern = "intern";
    const char *exteern = "extern";
    char *ptr = NULL;
    const char *get = "GET";
    const char *http = "HTTP/";
    const char *http_Nr = "1.1";
    if (memcmp(meth, get, 3) != 0) {
        return 501;
    }   else if(strncmp(protocol, http, strlen(http)) != 0) {
        return 400;
    }
    else if(strncmp(protocol+strlen(http), http_Nr, strlen(http_Nr)) != 0) {
        return 501;}
    else if (strlen(ress) == 0) {
        return 400;   //leere Resource ==> 400 Bad Request
    } else if (host == NULL){
        return 400;
    } else if (strlen(host) == 0){
        return 400;
    }
    else if ( (strcmp(localhost, host) == 0 || strcmp(host, localnb) == 0)  ){
        char *test =calloc(1,PATH_MAX);
        if (test == NULL)
            exit(2);
        getcwd(test,PATH_MAX);

        if(strcmp(test, startDir) != 0){
            chdir("../../");
        }
        chdir("default/");

        free(test);

        ptr = realpath(ress, NULL);

        if (ptr == NULL) {

            // Der Pfad existiert nicht, aber liegt er wenigstens im DocRoot?

            char *old = calloc(1, PATH_MAX);
            if (old == NULL) {
                exit(1);
            }
            realpath(ress, old);


            if (strncmp(DOC_ROOT_DEFAULT, old, strlen(DOC_ROOT_DEFAULT)) == 0) {
                free(ptr);
                free(old);
                return 404;  //Pfad existiert nicht + innerhalb DocRoot ==> 404 Not Found
            } else {
                free(old);
                free(ptr);
                return 403; // Pfad existiert nicht + außerhlab DocRoot ==> 403 Forbidden
            }
        } else {

            // Der Pfad existiert, aber liegt er im DocRoot?

            if (strncmp(DOC_ROOT_DEFAULT, ptr, strlen(DOC_ROOT_DEFAULT)) == 0&&strncmp(host,localhost,9)==0) {
                free(ptr);
                return 200;  // Pfad existiert + innerhalb DocRoots ==> 200 OK
            } else {
                free(ptr);
                return 403; // der Pfad existiert + außerhalb DocRoots ==> 403 Forbidden
            }
        }
    }


        /*
         *  wenn Host == extern
         */
    else if ((strcmp(host,exteern) == 0) ) {
        chdir("extern/");

        ptr = realpath(ress, NULL);

        if (ptr == NULL) {

            // Der Pfad existiert nicht, aber liegt er wenigstens im DocRoot?

            char *old = calloc(1, PATH_MAX);
            if (old == NULL)
                exit(1);
            realpath(ress, old);


            if (strncmp(DOC_ROOT_EXTERN, old, strlen(DOC_ROOT_EXTERN)) == 0) {
                free(ptr);
                free(old);
                return 404;  //Pfad existiert nicht + innerhalb DocRoot ==> 404 Not Found
            } else {
                free(old);
                free(ptr);
                return 403; // Pfad existiert nicht + außerhlab DocRoot ==> 403 Forbidden
            }
        } else {

            // Der Pfad existiert, aber liegt er im DocRoot?

            if (strncmp(DOC_ROOT_EXTERN, ptr, strlen(DOC_ROOT_EXTERN)) == 0) {
                free(ptr);
                return 200;  // Pfad existiert + innerhalb DocRoots ==> 200 OK
            } else {
                free(ptr);
                return 403; // der Pfad existiert + außerhalb DocRoots ==> 403 Forbidden
            }
        }


    }
        /*
        *  wenn Host == intern
        */
    else if ((strcmp(host, intern) == 0) ){
        chdir("intern/");

        ptr = realpath(ress, NULL);


        if (ptr == NULL) {

            // Der Pfad existiert nicht, aber liegt er wenigstens im DocRoot?

            char *old = calloc(1, PATH_MAX);
            if (old == NULL)
                exit(1);
            realpath(ress, old);


            if (strncmp(DOC_ROOT_INTERN, old, strlen(DOC_ROOT_INTERN)) == 0) {
                free(ptr);
                free(old);
                return 404;  //Pfad existiert nicht + innerhalb DocRoot ==> 404 Not Found
            } else {
                free(old);
                free(ptr);
                return 403; // Pfad existiert nicht + außerhlab DocRoot ==> 403 Forbidden
            }
        } else {

            if(strncmp(dateipfad,ptr,strlen(dateipfad)) == 0){
                free(ptr);
                return 403;
            }
            // Der Pfad existiert, aber liegt er im DocRoot?

            if (strncmp(DOC_ROOT_INTERN, ptr, strlen(DOC_ROOT_INTERN)) == 0 ) {
                free(ptr);
                return 401;  // Pfad existiert + innerhalb DocRoots ==> 401 damit im späteren switch case der richtige Fall eingeleitet wird
            } else {
                free(ptr);
                return 403; // der Pfad existiert + außerhalb DocRoots ==> 403 Forbidden
            }
        }


    }
    return 400;
}
// fin de la fct

/**
 * Die Funktion bekommt als Parameter die Strukturen "cntlen" und "body", die sie dann entsprechend dem "HTTP-Status : char_const" erstellt.
 * die erstellten Strukturen "body" und "cntlen" werden dann in die Response "erstelinie" geschrieben, und diese wird dann am Ende zurückgegeben
 * @param string*: erstelinie, die Struktur die unsere Response darstellt, in die wir schreiben werden
 * @param string*: cntlen, die Struktur, die unseren HTTP-Header "Content-Length" enthalten wird
 * @param string*: body, die Struktur, die unseren HTTP-Body enthalten wird
 * @param const char*: char_cons,t die konstante Zeichenkette entspricht der "HTTP-Status", der der Funktion übergeben wird
 * @author pse1pg03
 * @return string*: die Funktion gibt die Struktur "erstelinie" zurück, nachdem die "HTTP-Body" und der Header "Content-Length"
 * in diese Struktur geschrieben wurden
 *
 */
string *statcode_to_string(string *erstelinie, string *cntlen, string *body, const char *char_const) {

    int nchars_cntlen, nchars_body;
    nchars_cntlen = snprintf(cntlen->str, cntlen->len, "Content-Length: %zu \r\n\r\n",
                             LEERES_BODY + strlen(char_const));
    if (nchars_cntlen >= cntlen->len) {
        cntlen->str = realloc(cntlen->str, (nchars_cntlen + 1) * 2);
        if (cntlen->str == NULL) {
            exit(4);
        }
        cntlen->len = (nchars_cntlen + 1) * 2;
        nchars_cntlen = snprintf(cntlen->str, cntlen->len, "Content-Length: %zu \r\n\r\n",
                                 LEERES_BODY + strlen(char_const));
    }
    cntlen->pos = nchars_cntlen - 1;
    erstelinie = str_cat(erstelinie, cntlen->str, nchars_cntlen);
    nchars_body = snprintf(body->str, body->len, "<html>\n"  //7
                                                 " <body>\n" //8
                                                 "  <h1>%s</h1>\n" //15
                                                 "  <pre> \n" //9
                                                 "  </pre>\n"  //8
                                                 " </body>\n"   //9 +8
                                                 "</html> ", char_const);
    if (nchars_body >= body->len) {
        body->str = realloc(body->str, (nchars_body + 1) * 2);
        if (body->str == NULL) {
            exit(4);
        }
        body->len = (nchars_body + 1) * 2;
        nchars_body = snprintf(body->str, body->len, "<html>\n"  //7
                                                     " <body>\n" //8
                                                     "  <h1>%s</h1>\n" //15
                                                     "  <pre> \n" //9
                                                     "  </pre>\n"  //8
                                                     " </body>\n"   //9 +8
                                                     "</html> ", char_const);
    }
    body->pos = nchars_body - 1;
    erstelinie = str_cat(erstelinie, body->str, body->pos + 1);
    free_str(cntlen);

    return erstelinie;
}