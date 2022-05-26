#include "httplib.h"
#include "request.h"

/** Testet die gegeben request auf fehler und gibt entsprechende codes zurück
 *
 *
 * @param Die request als string* und den Host als char*
 * @return Fehlercode als int
 */
int testGet(string * request,char * host) {

    int str_len=1024, c=0 , count=0 ;
    size_t kurze = 40;
//char* werden festgelegt um später mit der Request zu vergleichen
    char * get = "GET";
    char * http1 = "HTTP/1.1";
    char * http = "HTTP";
//Speicher um HTTP Methode und Version zu speichern
    char* method = calloc(kurze,1);
    if (method==NULL)
        exit(2);
    char* version = calloc(kurze,1);
    if (version==NULL)
        exit(2);

 while (request->str[count]==' '){
     count++;
 }


int k=0;
    //Die Methode wird heraus gelesen
    for(count ;request->str[count] != ' ' && count < kurze;count++,k++){
        method[k]=request->str[count];
    }
    if(count==0 || count>=40){
        free(version);
        free(method);
        return 400;
    }
    //falls die Methode nicht gleich Get ist wird mit 501 geendent
    if (strncmp(method,get,  3)!=0 ) {
        free(version);
        free(method);
        return 501;
    }
    count++;

    //request->str[count] != 'H' && request->str[count+1] != 'T' && request->str[count+2] != 'T' && request->str[count+3] != 'P' && request->str[count+4] != '1' && request->str[count+5] != '/' && request->str[count+6] != '1'
    //int i=0;request->str[count] != ' ' && request->str[count+1] != 'H' && i < str_len;count++,i++

    for (count;request->str[count] != '/'; count++) {

    }
    int i=0;

        for (count; request->str[count] != ' '; count++) {

        }

        for (count; request->str[count] == ' ' && i==0; count++) {
            char *temp = &request->str[count];
            if (strncmp(temp, http1, strlen(http1)) == 0) {
              i=1;
            }
        }



    //Falls keien Pfad angegeben wurde stopt count bei 4
    if (count==4){
        free(version);
        free(method);
        return 400;
    }
    //Sollte der Pfad über 1024 Zeichen lang sein wird er auch nicht akzeptiert
    if(count >= str_len ){
        free(version);
        free(method);
        return 414;
    }
    // Pfad enthält den decodeten Teil der von realpath genutzt werden kann
    // Adresse soll den richtigen Dateipfad halten
    string * pfad= uri_decoder(request);

    //ist kein Pfad enthalten
    if (pfad->pos==0){
        free_str(pfad);
        free(version);
        free(method);
        return 400;
    }
    string* adresse=new_string(1);

    //getHost gibt FalscherHost zurück wenn der Host flasch geschrieben wurde
    if(strcmp(host,"falscherHost")==0){
        free_str(pfad);
        free_str(adresse);
        free(version);
        free(method);
        return 400;
    }
    //Je nach Host wird einanderer Dateipfad genutzt
    if(strcasecmp(host,"INTERN")==0)
        str_cat(adresse,INTERN,strlen(INTERN));
    else if(strcasecmp(host,"EXTERN")==0)
        str_cat(adresse,EXTERN,strlen(EXTERN));
        //else if(strcasecmp(host,"")==0)
        // str_cat(adresse,DOC_ROOT,strlen(DOC_ROOT));
    else if(strcasecmp(host,"LOCALHOST")==0)
        str_cat(adresse,DOC_ROOT,strlen(DOC_ROOT));
    else{
        free_str(adresse);
        free(version);
        free(method);
        free_str(pfad);
        return 403;
    }

    str_cat(adresse,pfad->str,pfad->pos+1);
    //Wenn Pfad leer ist wird NULL angehängt
    str_cat(adresse,"\0",1);
    free_str(pfad);


    // version wird heraus gelesen und Überprüft
    for(int i=0;request->str[count] != '\r' && request->str[count+1] != '\n' && i < kurze;count++,i++){
        version[i]=request->str[count];
    }
    //Sollte die angegebene Version nicht existiren
    if (strncmp(http ,version, strlen(http)) != 0){
        free_str(adresse);
        free(version);
        free(method);
        return 400;
    } else if (strncmp(http1,version, strlen(http1)) != 0) {
        // Die Version existtiert zwar aber wird nicht unterstützt
        free_str(adresse);
        free(version);
        free(method);
        return 505;
    }

    c= test(adresse->str, host);

    free_str(adresse);
    free(version);
    free(method);
    return c;
}
/** Funktion erhält ein Pfad welcher auf richtigkeit und existenz geprüft werden soll
 *
 * @param unbereinigter Pfad und Host als char*
 * @return Gibt fehlercode 403/404 zurück
 */
int test( char* tes, char * host) {
    //Der Pfad wird durch realpath bereinigt
    char *ptr = realpath(tes, NULL);
    int c =0;
    //wenn realpath NULL zurück gibt existiert der Pfad nicht
    if(ptr == NULL) {
        free(ptr);
       return 404;
    } else {
        // Der Pfad existiert, aber liegt er im DocRoot?
        if(strncmp(DOC_ROOT, ptr, strlen(DOC_ROOT)) == 0) {

        } else if ((strncmp(INTERN, ptr, strlen(INTERN)) == 0) && strncasecmp(host,"INTERN",strlen("INTERN"))==0){

        } else if ((strncmp(EXTERN, ptr, strlen(EXTERN)) == 0) && strncasecmp(host,"EXTERN",strlen("EXTERN"))==0){

        } else {
            c= 403;
        }
    }

    free(ptr);
    return c;
}
/** Funktion realloziert den char *str der uebergebenen String Struktur.
 * @author Jannick Weelink (jw108928)
 *
 * @param str - die zu reallozierende String Struktur.
 * @param new_len - die neue Groesse.
 */
void re_alloc(string *str, size_t new_len) {
    str->str = realloc(str->str, new_len);

    if(str->str == NULL) {
        puts("Das reallozieren ist fehlgeschlagen. \n");
        exit(2);
    }

    str->len = new_len;
}
/** Funktion liest die URI aus dem eingehendem Request aus.
 * @author Jannick Weelink (jw108928)
 *
 * @param tmp - eigene String Struktur fuer die URI.
 * @param request - die eingehende (kodierte) request.
 */
void get_uri(string *tmp, const string *request) {
    size_t get_index = 0, index = 0;

    // Den Anfang der URI ermitteln.
    while(request->str[get_index] != '/' && get_index <= request->pos ) {
        get_index++;
    }

    for(index = 0; request->str[get_index] != ' ' && get_index < request->len-1  ; index++) {
        // Index startet bei 0, wie der String, die Laenge bei 1.
        // Der Speicher muss vergroessert werden.
        if(index == (tmp->len - 1)) {
            re_alloc(tmp, (tmp->len * 2));
        }

        tmp->str[index] = request->str[get_index];
        tmp->pos++;
        get_index++;
    }

    // position ist das letzte Zeichen, nicht eine Art Nullbyte.
    tmp->pos--;
}
/** Fand ich fuer meine Zwecke besser als cpy_str / new_string.
 * @author Jannick Weelink (jw108928)
 *
 * @param len - die maximale laenge des char-Strings.
 * @return die String Struktur.
 */
string *create_string(size_t len) {
    string *str;

    if((str = calloc(1, sizeof(string))) == NULL) {
        exit(1);
    }
    if((str->str = calloc(len, sizeof(char))) == NULL) {
        exit(1);
    }

    str->len = len;
    str->pos = 0;
    return str;
}
/** Funktion sucht nach %-Zeichen inerhalb der URL, weist die naechsten zwei Zeichen einem
 * String zu, konvertiert den Hexadezimalen String in einen Int und konvertiert diesen anschliessend
 * in einen Char.
 * Wichtig: Die Struktur 'http_resource' muss vom Aufrufer freigegeben werden.
 * Wichtig: Funktion ist nur fuer ASCII definiert -> Umlaute waeren nicht moeglich.
 * @author Jannick Weelink (jw108928)
 *
 * @param request - Die HTTP Request.
 * @return String Struktur mit der decodierten URL, gespeicher in ->str.
 */
string* uri_decoder(const string *request) {
    string *http_resource, *tmp;
    size_t str_len = 2048;
    int i = 0, j = 0;   // index Variablen
    int x = 0;          // hex to int wert
    char str[] = "00";  // haelt den hexadezimalwert nach dem % zeichen
    char c = '0';       // int to char wert
    char * error = "/default/error_400.html";

    if(str_len < strlen(request->str)){
        http_resource = create_string(str_len);
        str_cat(http_resource,error, strlen(error));
        http_resource->pos=strlen(error);
        return http_resource;
    }

    tmp = create_string(str_len);           // Struktur wird erstellt
    http_resource = create_string(str_len); // Struktur wird erstellt
    get_uri(tmp, request);   // Die Request URL wird in einen temporaeren String kopiert.


    // Decodierung: Nur fuer ASCII definiert!
    for(i = 0; j <= tmp->pos; i++) {
        // Ist der reservierte Speicher gross genug?
        if(i == (http_resource->len - 1)) {
            re_alloc(http_resource, (http_resource->len * 2));
        }

        if(tmp->str[j] == '%' && j<=tmp->len ) {
            str[0] = tmp->str[j + 1];
            str[1] = tmp->str[j + 2];
            j = j + 2;

            x = (int)strtol(str, NULL, 16);
            c = (char)x;

            http_resource->str[i] = c;
        }
        else {
            http_resource->str[i] = tmp->str[j];
        }

        http_resource->pos++;
        j++;
    }
    http_resource->pos--;

    free_str(tmp);  // tmp wird nicht mehr gebraucht.
    return http_resource;
}

/** Funktion alle leerzeichen werden entfernt und toupper()
 *
 * @param string
 * @return string der bereinigt wurde
 */
string* request_bereinigen(string* req){
    // alle leerzeichen werden entfernt und toupper()
    int i=0,new_pos=0;
    string* clean=new_string(1);
    str_cat(clean,req->str,req->pos);
    case_dont_matter_at_all(clean);

    for(i;i<clean->pos;i++){
        if(clean->str[i]!=' ') {

            clean->str[new_pos]=clean->str[i];
            new_pos++;
        }

    }
    clean->pos=new_pos;
    return clean;
}

/** Funktion die den host sucht und auf ein char* schreibt
 *
 * @param string request
 * @return char* host
 */
char* getHost(string* request){
    int i=0,j=0;
    // gesäuberten request durchgehen bis man "HOST" findet
    while (i<request->pos){
        if(request->str[i]==':')
        {
            if(request->str[i-1]=='T'&&request->str[i-2]=='S'&&request->str[i-3]=='O'&&request->str[i-4]=='H')
                break ;

        }
        i++;
    }
    // Keine host gefunden
    if(i==request->pos){
        return "falscherHost";
    }
    j=i+1;
    while (request->str[j]!=':'&&request->str[j]!='\r'&&request->str[j]!='\n')
        j++;

    //index i&j sind anfang und ende des hosts
    char*host =calloc(j-i+1,1);
    if(host == NULL){
        exit(2);
    }
    for(int k=0;k<j-i-1;k++)
        //host auf host schreiben und zurückgeben
        host[k]=request->str[i+1+k];
    return host;
}