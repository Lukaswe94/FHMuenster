/*! \mainpage PSE 1 pg 04
 * \author pse1pg03
 *
 * \author Übernommen und weiter entwickelt von: Tim Lause, Jannik Weelink, Kai Wulfert, Kenan Sharifa
 *
 * \version Version: 1.0
 *
 * Localer Server zum Anfragen und Ausgeben basic websites
 *
 */

#include <errno.h>      // errno
#include <netinet/ip.h> // ^
#include <signal.h>     // sigaction, struct sigaction, siginfo_t, SIGTERM
#include <stdbool.h>    // bool
#include <stdio.h>      // fprintf
#include <stdlib.h>     // exit, malloc, free
#include <string.h>     // memset, strerror
#include <sys/socket.h> // struct sockaddr_in, socket, setsockopt, bind, listen, socklen_t, accept
#include <unistd.h> // read, write, close
#include "httplib.h"
#include "base64.h"
#include "error_handeling.h"
#include "file_handeling.h"
#include "authentication_handeling.h"
#include "request_handeling.h"

#define PORT 31337
#define BUFFER_SIZE (1024*1024)
#define LEERES_BODY 61
#define INIT_SIZE 150




string *process(string *request);

static bool run = true;

/**
 * Gibt eine Fehlermeldung *msg* aus und beendet das Programm.
 * @param msg Die Fehlermeldung.
 */
static void error(char *msg) {
    fprintf(stderr, "%s", msg);
    if (errno) {
        fprintf(stderr, ", errno: %s", strerror(errno));
    }
    fprintf(stderr, "\n");
    exit(1);
}

/**
 * Diese Funktion wird aufgerufen, wenn das Programm das *SIGINT*-Signal empfängt. Es beendet den Server.
 * @param int signum Die Signalnummer.
 */
static void handle_signal(int signum) {
    if (signum != SIGINT) {
        error("ERROR unexpected signal");
    }

    /*
     * Beende den Server nach dem Abarbeiten des letzten Clients.
     */
    run = false;
}

/**
 * Registriert das SIGINT-Signal (Strg+C) um den Server beenden zu können.
 */
static void register_signal() {
    struct sigaction action;

    /*
     * Konfigurieren des Signal-Handlers.
     */
    memset(&action, 0, sizeof(action));
    action.sa_handler = handle_signal;

    /*
     * Registrierung des Signal-Handlers.
     */
    if (sigaction(SIGINT, &action, NULL) < 0) {
        error("ERROR registering signal handler");
    }
}

/**
 * Erstellt und konfiguriert den Netzwerk-Socket, über den die Verbindungen
 * angenommen werden.
 */
static int setup_socket() {
    int opt = 1;
    int sockfd = 0;
    struct sockaddr_in serv_addr;

    /*
     * Setzt Konfigurationsvariablen für den Socket, z.B. die Portnummer.
     */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    /*
     * Erstelle den Socket.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    /*
     * Verwende den Socket, selbst wenn er aus einer vorigen Ausführung
     * im TIME_WAIT Status ist.
     */
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &opt,
                   sizeof(int)) < 0)
        error("ERROR on setsockopt");

    /*
     * Melde, dass der Socket eingehende Verbindungen akzeptieren soll.
     */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    /*
     * Horche auf dem Socket nach eingehenden Verbindungen. Es werden maximal
     * fünf gleichzeitige Verbindungen erlaubt.
     */
    if (listen(sockfd, 5) < 0) {
        error("listen");
    }
    return sockfd;
}

static void main_loop_stdin() {
    void *const buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        error("ERROR at malloc.");
    }

    /*
     * Lies die ankommenden Daten von dem Socket in das Array buffer.
     */
    memset(buffer, 0, BUFFER_SIZE);
    size_t length = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (length < 0) {
        if (errno != EINTR) {
            error("ERROR reading from socket");
        }
    }

    string *request = cpy_str(buffer, length);
    string *response = process(request);

    size_t response_len = get_length(response);
    char *response_char = get_char_str(response);
    /*
     * Schreibe die ausgehenden Daten auf stdout.
     */
    if (write(STDOUT_FILENO, response_char, response_len) < 0) {
        error("ERROR writing to STDOUT");
    }

    free_str(response);
    free(buffer);
}

/**
 * Die Hauptschleife, in der eingehende Verbindungen angenommen werden.
 */
static void main_loop() {
    const int sockfd = setup_socket();
    int newsockfd;
    ssize_t length;

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    void *const buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        error("ERROR at malloc.");
    }

    /*
     * Die Hauptschleife des Programms.
     */
    while (run) {

        /*
         * Der accept()-Aufruf blockiert, bis eine neue Verbindung rein kommt.
         */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            /*
             * Wenn der Server mit dem SIGINT-Signal beendet wird, schlägt accept
             * mit EINTR (interrupted) fehl.
             */
            if (errno == EINTR) {
                break;
            }
            error("ERROR on accept");
        }

        /*
         * Lies die ankommenden Daten von dem Socket in das Array buffer.
         */
        memset(buffer, 0, BUFFER_SIZE);
        length = read(newsockfd, buffer, BUFFER_SIZE - 1);
        if (length < 0) {
            if (errno == EINTR) {
                break;
            }
            error("ERROR reading from socket");
        }
        string *request = cpy_str(buffer, length);
        string *response = process(request);

        /*
         * Schreibe die ausgehenden Daten auf den Socket.
         */
        size_t response_len = get_length(response);
        char *response_char = get_char_str(response);
        length = write(newsockfd, response_char, response_len);
        if (length < 0) {
            error("ERROR writing to socket");
        }
        free_str(response);
        free_str(request);
        /*
         * Schließe die Verbindung.
         */
        if (close(newsockfd) < 0) {
            error("ERROR on close");
        }
    }

    free(buffer);
    if (close(sockfd) < 0) {
        error("ERROR on close");
    }
}

/**
 * Die Funktion akzeptiert den eingehenden Request und gibt eine entsprechende Response zurück.
 * @param string*: request Der eingehende Request.
 * @return string*: Die ausgehende Response.
 */
string *process(string *request) {

    if(request->pos > 10000000000000000000) // manchmal wird aus Gründen die wir nicht kennen eine leere Request mit einer 19 Stelliigen Pos gesendet
        request->pos=0;


    string *method=NULL;
    string *resource = NULL;
    string *protocol = NULL;
    string *erstelinie = NULL;
    string *aktuell = NULL;
    string *authentication = NULL;
    string *searchHost = NULL;
    string *hostt = NULL;
    chdir("cmake-build-debug/docroot/");
    chdir("docroot/");
    /*
     * Deklaration von konstanten Zeichenkette für die erste Linie und für ein paar Header
     */
    const char *index ="/index.html";
    const char *http = "HTTP/1.1 ";
    const char *const_ok = "200\r\n";
    const char *const_forbid = "403\r\n";
    const char *const_notfnd = "404\r\n";
    const char *const_notimp = "501\r\n";
    const char *const_badreq = "400\r\n";
    const char *const_unauth = "401\r\n";
    const char *const_URI_lang = "414\r\n";
    const char *auth_header = "WWW-Authenticate: basic\r\n";
    char *startDir = calloc( PATH_MAX,1);
    if (startDir == NULL)
        exit(2);
    getcwd(startDir,PATH_MAX);
    size_t startDir_len =strlen(startDir);
    char* DOC_ROOT_DEFAULT =calloc( startDir_len+9,1);      //zuweisung des richtigen Dateipfades
    if (DOC_ROOT_DEFAULT == NULL) {
        exit(4);
    }
            memcpy(DOC_ROOT_DEFAULT,startDir,startDir_len);
            strcat(DOC_ROOT_DEFAULT,"/default");
    char* DOC_ROOT_EXTERN = calloc( startDir_len+9,1);
    if (DOC_ROOT_DEFAULT == NULL) {
        exit(4);
    }
    memcpy(DOC_ROOT_EXTERN,startDir,startDir_len);
    strcat(DOC_ROOT_EXTERN,"/extern");
    char* DOC_ROOT_INTERN  =calloc( startDir_len+9,1);
    if (DOC_ROOT_INTERN == NULL) {
        exit(4);
    }
    memcpy(DOC_ROOT_INTERN,startDir,startDir_len);
    strcat(DOC_ROOT_INTERN,"/intern");

    const char *dateipfad =calloc( startDir_len+18,1);
    if (dateipfad == NULL) {
        exit(4);
    }
    memcpy(dateipfad,DOC_ROOT_INTERN,strlen(DOC_ROOT_INTERN));
    strcat(dateipfad,"/htpasswd");

    /*
     * Deklaration einer string Struktur für den Body
     */
    string *body = new_string(INIT_SIZE);
    body->len = INIT_SIZE * 2;

    int  nchars_cntlen;

    /*
     * string Struktur für den Header "Content-Length"
     */
    string *cntlen = new_string(INIT_SIZE);
    int status_code;

    /*
     * Auslesen von der "HTTP Methode", "HTTP Resource" und "HTTP Version" von der Request, durch die Funktion "get_part"
     */
    method = get_part(request, 0);
    if(method != NULL) {
        resource = get_part(request, strlen(method->str) + 1);
    }
    else resource = get_part(request,0);

    if(resource != NULL) {
        protocol = get_part(request, (strlen(method->str) + strlen(resource->str)) + 2);
        if(strncmp(resource->str, "/",resource->pos+1)==0){
            free_str(resource);
            resource = cpy_str(index, strlen(index));
        }


    }
    else if(method == NULL) protocol = get_part(request, 0);
    else protocol = get_part(request, strlen(method->str)+2);




    /*
     * Auslesen vom "HTTP-Request-Header" "Host" druch die Funktion "get_host"
     */
    searchHost = cpy_str(request->str, request->pos+1);
    searchHost->str = lower(searchHost);
    hostt = get_host(searchHost);
    free_str(searchHost);

    /*
     * Protocoll wird an den Anfang der response gehängt
     */
     erstelinie = cpy_str("HTTP/1.1 ", 9);//protocol am Anfang der response kopieren

    /*
     * hexReplace um hex-zeichen die im Namen der resource vorkommen können zu ersetzen, wenn keins vorkommt wird resource zurückgegeben
     */
    if(resource != NULL) resource = hexReplace(resource);
    /*
     * Es wird erstmal überprüft, ob die keine "Resource" angegeben wurde oder ob in der Request keine "HTTP-Version" drin steht.
     * Wenn ja, dann bekommt die Variable "status_code" den Wert 400 zugewiesen,
     * wenn nicht dann wird der den "status_code" durch die Funktion "get_status_code_2" übermittelt
     * Für den fall das Protocol == NULL ist kopieren wir HTTP/1.1 in den Protocol String um ein Absturz des Servers zu vermeiden
     */
    if (resource !=NULL && strlen(resource->str) > PATH_MAX) { // der Empfangene Datenstrom soll nicht länger als 1 MB sein
        if(protocol != NULL)
            free_str(protocol);
        if(erstelinie != NULL)
            free_str(erstelinie);
        status_code = 414;
        protocol = cpy_str(http, strlen(http));
        erstelinie = cpy_str("HTTP/1.1 ", 9); //
    }
    else if (method == NULL || protocol == NULL || resource == NULL || hostt == NULL) {
        if(protocol != NULL)
            free_str(protocol);
        if(erstelinie != NULL)
            free_str(erstelinie);
        status_code = 400;
        protocol = cpy_str(http, strlen(http));
        erstelinie = cpy_str("HTTP/1.1 ", 9);
    } else {

        status_code = get_status_code(resource->str + 1, method->str, hostt->str,protocol->str, DOC_ROOT_INTERN,  DOC_ROOT_EXTERN, DOC_ROOT_DEFAULT,startDir,dateipfad);
    }
    /*
     * nachdem der HTTP-Request-Header "Host" ausgewertet und für die Bestimmung von "status_code" benutzt wurde, geben wir den entsprechenden Speicher frei
     */
    if (hostt != NULL) free_str(hostt);

    /*
     * Je nach dem Wert von "status_code" wird eine "HTTP Status" in "erstelinie" hinzugefügt
     */
    switch (status_code) {
        case 200:
            erstelinie = str_cat(erstelinie, const_ok, strlen(const_ok));
            break;
        case 400:
            erstelinie = str_cat(erstelinie, const_badreq, strlen(const_badreq));
            break;
        case 403:
            erstelinie = str_cat(erstelinie, const_forbid, strlen(const_forbid));
            break;
        case 404:
            erstelinie = str_cat(erstelinie, const_notfnd, strlen(const_notfnd));
            break;
        case 501:
            erstelinie = str_cat(erstelinie, const_notimp, strlen(const_notimp));
            break;
        case 401:{

            /*
            * B_P ausgabe soll nur beim Aufruf einer Index Seite statt finden und nicht bei jedem Bild,js-datei,... einzelnd
            */
            size_t * out_len = calloc(1,sizeof(size_t));
            if(out_len == NULL)
                exit(2);
            unsigned char *auslese1 = getRequestAuthorization(request);     // verschlüsselte authorization wird ausgelesen
            if (auslese1 == NULL || *auslese1 == NULL){
                erstelinie = str_cat(erstelinie, const_unauth, strlen(const_unauth));
                free(out_len);
                free(auslese1);
                break;
            }
            char * auslese = entschlusseln(auslese1, out_len);
            if (strncmp(resource->str, index, strlen(index))==0)
                B_P_ausgabe(auslese);

            string * lesbar = getPw(auslese); // authorization wird in die richtige Form gebracht

            if (lesbar == NULL){
                erstelinie = str_cat(erstelinie, const_unauth, strlen(const_unauth));
                free(auslese);
                free(out_len);
                free_str(lesbar);
                free(auslese1);
                break;
            }

            int check = pswd_vergleich(lesbar->str,dateipfad);  // vergleich mit paswd
            if (check == 1&& status_code == 401){
                erstelinie = str_cat(erstelinie, const_ok, strlen(const_ok));
                status_code = 200;

                char *test =calloc(1,PATH_MAX);
                if(test == NULL)
                    exit(2);
                getcwd(test,PATH_MAX);

                if(strcmp(test, startDir) != 0){
                    chdir("../../");
                }
                free(test);
                chdir("docroot/intern/");

            } else {
                erstelinie = str_cat(erstelinie, const_unauth, strlen(const_unauth));
            }
            free(auslese);
            free(out_len);
            free_str(lesbar);
            free(auslese1);
            break;
        }
        case 414:
            erstelinie = str_cat(erstelinie, const_URI_lang, strlen(const_URI_lang));
            break;
        default:
            break;
    }



    /*
     * Deklaration von konstanten Zeichenketten für den Header "Content-Type"
     */

    const char *jpg = ".jpg";
    const char *png = ".png";

    const char *const_html = "Content-Type: text/html\r\n";
    const char *const_css = "Content-Type: text/css\r\n";
    const char *const_jpeg = "Content-Type: image/jpeg;q=0.8\r\n";
    const char *const_java = "Content-Type: application/x-javascript\r\n";
    const char *const_png = "Content-Type: image/png\r\n";
    const char *const_ogg = "Content-Type: video/ogg\r\n";
    const char *const_gif = "Content-Type: image/gif\r\n";
    const char *const_text = "Content-Type: text/html;charset=UTF-8\r\n";

    /*
     * Je nach der übergebenene "Resource" wird ein entsprechender "Content-Type" (cnttp) erzeugt
     */
    string *cnttp;
    char *ext;
    if(resource != NULL) ext = memchr(resource->str, '.', resource->pos + 1);
    else ext = NULL;
    string *temp = NULL;
    if (ext != NULL) {
        temp = cpy_str(ext, strlen(ext));
        temp->str = lower(temp);
    }
    if (temp == NULL) {
        cnttp = cpy_str(const_html, strlen(const_html));
        cnttp->pos = strlen(const_html) - 1;
    } else if (memcmp(temp->str, jpg, strlen(jpg)) == 0) {// jpg u. JPG
        cnttp = cpy_str(const_jpeg, strlen(const_jpeg));
        cnttp->pos = strlen(const_jpeg) - 1;
    } else if (memcmp(temp->str, ".js", strlen(".js")) == 0) {
        cnttp = cpy_str(const_java, strlen(const_java));
        cnttp->pos = strlen(const_java) - 1;
    } else if (memcmp(temp->str, png, strlen(png)) == 0) {
        cnttp = cpy_str(const_png, strlen(const_png));
        cnttp->pos = strlen(const_png) - 1;
    }else if (memcmp(temp->str, ".ogg", strlen(".ogg")) == 0) {
        cnttp = cpy_str(const_ogg, strlen(const_ogg));
        cnttp->pos = strlen(const_ogg) - 1;
    }else if (memcmp(temp->str, ".gif", strlen(".gif")) == 0) {
        cnttp = cpy_str(const_gif, strlen(const_gif));
        cnttp->pos = strlen(const_gif) - 1;
    }else if (memcmp(temp->str, ".css", strlen(".css")) == 0) {
        cnttp = cpy_str(const_css, strlen(const_css));
        cnttp->pos = strlen(const_css) - 1;
    }
    else {
        cnttp = cpy_str(const_text, strlen(const_text));
        cnttp->pos = strlen(const_text) - 1;
    }

    /*
     * der gearde erstellte "Content-Type" Header wird in die "erstelinie" hinzugefügt, und dann wird der vorher von ihm besetzten Speicher freigegeben
     */
    if(temp != NULL){
        free_str(temp);
    }
    erstelinie = str_cat(erstelinie, cnttp->str, cnttp->pos + 1);
    free_str(cnttp);


    /*
     * Je nach dem Wert von "status_code" wird ein enstprechender "HTTP-Body" und  "HTTP-Conten-Length-Header" erstellt
     */
    switch (status_code) {
        case 200:

                /*
                 * Öffnen einer Datei mit der Funktion fileTobdoy um diese in der Http response darzustellen
                 */
                aktuell = fileTobody(resource->str + 1);


            /*
             * Je nach der Länge unseres gerade erzeugten "HTTP-Body" wird der "Content-Length" Header in unsere Response hinzugefügt
             */
            if (aktuell == NULL){
                aktuell = new_string(1);
            }
            nchars_cntlen = snprintf(cntlen->str, cntlen->len, "Content-Length: %zu \r\n\r\n", aktuell->pos);
            /*
             * es wird überprüft, ob der bereits allozierten Speicher ausreichend war, um in die String Struktur "cntlen" unser Header schreiben zu können
             * ansonsten wird entsprechend der Anzahl der durch die "snprintf-Funktion" zu schreibenden Zeichen neuer Speicherbereich alloziert
             */
            if (nchars_cntlen >= cntlen->len) {
                cntlen->str = realloc(cntlen->str, (nchars_cntlen + 1) * 2);
                if (cntlen->str == NULL) {
                    exit(4);
                }
                cntlen->len = (nchars_cntlen + 1) * 2;
                nchars_cntlen = snprintf(cntlen->str, cntlen->len, "Content-Length: %zu \r\n\r\n", aktuell->pos);
            }

            /*
             * die Länge von "cntlen " wird aktualisiert,
             *und der erzeugte "Content-Lenght" Header wird in die Response geschrieben
             * der benutzte Speicherbereich wird freigegeben
             */
            cntlen->pos = nchars_cntlen - 1;
            erstelinie = str_cat(erstelinie, cntlen->str, cntlen->pos + 1);
            free_str(cntlen);

            /*
             * Jetzt können wir unser "HTTP-Body" in die Response schreiben
             */

            erstelinie = str_cat(erstelinie, aktuell->str, aktuell->pos );




                free_str(aktuell);


            break;

            /*
             * in den nächsten Fällen werden Je anch dem "status_code" die passenden "Content-Lenght-Header" und der "HTTP-Body"
             * durch die Funktion "statcode_to_string" in die Response geschrieben
             */
        case 400:
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_badreq);
            break;
        case 414:
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_badreq);
            break;

        case 403:
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_forbid);
            break;

        case 404:
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_notfnd);
            break;

        case 501:
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_notimp);
            break;

        case 401:
            /*
             * Im 401-Error Fall fügen wir als erstes in unsere String Struktur "authentification" den HTTP-Header "WWW-Authenticate: basic\r\n"
             */
            authentication = cpy_str(auth_header, strlen(auth_header));
            authentication->pos = strlen(auth_header) - 1;

            /*
             * in die response werden wird dann die gerade erstellen String Struktur "authentification" geschrieben
             * dazu werden die passenden "Content-Lenght-Header" und der "HTTP-Body" durch die Funktion "statcode_to_string" geschrieben
             */
            erstelinie = str_cat(erstelinie, authentication->str, authentication->pos + 1);
            free_str(authentication);
            erstelinie = statcode_to_string(erstelinie, cntlen, body, const_unauth);
            break;

        default:
            break;
    }
    char *tester =calloc(1,PATH_MAX);
    if (tester == NULL)
        exit(2);
    getcwd(tester,PATH_MAX);

    if(strncmp(tester, DOC_ROOT_DEFAULT, strlen(DOC_ROOT_DEFAULT)) == 0){
        chdir("../../");
    }
    if(strncmp(tester, DOC_ROOT_INTERN, strlen(DOC_ROOT_INTERN)) == 0){
        chdir("../../");
    }
    if(strncmp(tester, DOC_ROOT_EXTERN, strlen(DOC_ROOT_EXTERN)) == 0){
        chdir("../../");
    }


    /*
     * Freigabe von benutzten Speicherbereichen
     */

    free_str(method);
    free_str(resource);
    free_str(protocol);
    free_str(body);
    free(DOC_ROOT_DEFAULT);
    free(DOC_ROOT_EXTERN);
    free(DOC_ROOT_INTERN);
    free(startDir);
    free(dateipfad);
    free(tester);

    string *response = erstelinie;
    return response;
}


int main(int argc, char *argv[]) {

    register_signal();
    if (argc == 2 && strcmp("stdin", argv[1]) == 0) {
        main_loop_stdin();
    } else {
        main_loop();
    }

    return 0;
}