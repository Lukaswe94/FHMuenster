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
#include "response.h"
#include "request.h"
#include <time.h>

#define PORT 31337
#define BUFFER_SIZE 1024*1024

string* process(string *request);

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
 * @param signum Die Signalnummer.
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

    free_str(request);
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
 * @param request Der eingehende Request.
 * @return Die ausgehende Response.
 */
string* process(string *request) {

    if(request->pos > 10000000000000000000)
        request->pos=0;
    int err=0, f=0;
    string* cleanreq=request_bereinigen(request);                                                                 //2. request ohne groß- & kleinschreibung oder Leerzeichen
    string* URL= uri_decoder(request);                                                                            //Url auslesen

    if(URL->str==NULL){
        err=400;
    }

    const  char* httpversion="HTTP/1.1 ";
    char* httpstatus;
    char* contenttype=getContenttype(URL);                                                                        //datentyp ermitteln
    const char* date="Date:";

    time_t time1=time(NULL);
    char* curtime=asctime(gmtime(&time1));

    char* host=getHost( cleanreq);                                                                                //Host ermitteln
    if(strcmp(host,"falscherHost")==0){
        f++;}
    char* WWW_Auth;

    char* body;
    string* adresse=new_string(1000);                                                                           //absoluten pfad zusammenstellen
    if(strcmp(host,"INTERN")==0)
        str_cat(adresse,INTERN,strlen(INTERN));                                                                 //pfad ist abhängig vom host
    else if(strcmp(host,"EXTERN")==0)
        str_cat(adresse,EXTERN,strlen(EXTERN));
    else
        str_cat(adresse,DOC_ROOT,strlen(DOC_ROOT));



    char * err403="/default/error_403.html\0";
    char * err404="/default/error_404.html\0";
    char * err400="/default/error_400.html\0";
    char * err501="/default/error_501.html\0";
    char * err401="/default/error_401.html\0";
    char * err414="/default/error_414.html\0";
    char * err505="/default/error_505.html\0";
    size_t errLang =strlen(err400);




    err= testGet(request, host);                                                                                     // pfad zu angefordeter ressource prüfen



    if(strcmp(host,"INTERN")==0) {
        err =401;

        httpstatus = "401\r\n";
        body="Authentication required";
        WWW_Auth ="WWW-Authenticate: 401 Unauthorized\r\nWWW-Authenticate: basic\r\n";
    }
    else {
        switch (err) {                                                                                            //Fallunterscheidung der Statuscodes
            case 0:
                str_cat(adresse, URL->str, URL->pos + 1);
                // str_cat(adresse,null,1);
                httpstatus = "200 OK\r\n";
                break;
            case 403:
                str_cat(adresse, err403, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "403\r\n";
                break;
            case 404:
                str_cat(adresse, err404, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "404\r\n";
                break;
            case 401:
                str_cat(adresse, err401, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "401\r\n";
                break;
            case 501:
                str_cat(adresse, err501, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "501\r\n";
                break;
            case 400:
                str_cat(adresse, err400, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "400\r\n";
                break;
            case 414:
                str_cat(adresse, err414, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "414\r\n";
                break;
            case 505:
                str_cat(adresse, err505, errLang);
                //str_cat(adresse,null,1);
                httpstatus = "505\r\n";
                break;
        }


        body = getFile(adresse->str);                                                           // im Fall eines Fehlers zeigt adresse auf eine Datei mit der Fehlermeldung
        if(body==NULL && err==0) {
            char*  error_404="/home/pseuser/CLionProjects/pse1pg04/DocRoot/default/error_404.html";
            httpstatus = "404\r\n";
            body=getFile(error_404);
            adresse=rewrite(adresse,error_404,strlen(error_404));


        }
    }
    //zusammenfügen der response
    string *response = new_string(1);

    str_cat(response,httpversion,strlen(httpversion));

    str_cat(response,httpstatus,strlen(httpstatus));

    str_cat(response,date,strlen(date));

    str_cat(response,curtime,strlen(curtime)-1);                                                      // curtime enthält \n --->strlen(curtime)-1

    str_cat(response,"\r\n",2);
    if(strcmp(host,"INTERN")==0)
        str_cat(response,WWW_Auth,strlen(WWW_Auth));

    int dateilange=getFilelen(adresse->str);
    char * lange= inttoStr(dateilange);

    size_t l = strlen("Content-length: ");

    str_cat(response,"Content-length: ",l);
    str_cat(response, lange,strlen(lange));
    str_cat(response,"\r\n",2);

    str_cat(response, contenttype,strlen(contenttype));

    if((strcmp(host,"INTERN")!=0)) {
        str_cat(response, body, getFilelen(adresse->str));
    } else{
        str_cat(response,body,strlen(body));
    }
    free(lange);
    free_str(URL);
    free_str(cleanreq);
    if(!(strcmp(host,"INTERN")==0))
        free(body);
    free_str(adresse);

    if (f==0){
        free(host);
    }

    return response;
}

int main(int argc, char *argv[]) {


    register_signal();

    if(argc == 2 && strcmp("stdin", argv[1]) == 0) {
        main_loop_stdin();
    } else {
        main_loop();
    }

    return 0;
}