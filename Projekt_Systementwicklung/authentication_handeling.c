//
// Created by pseuser on 16.06.20.
//

#include "httplib.h"
#include "base64.h"
#include "error_handeling.h"





/** Liest den Authentification Header aus.
 * Wichtig: getCode muss vom Aufrufer freigegeben werden.
 * @author Jannick Weelink (jw108928)
 *
 * @param string*: request
 * @return char*: Authentification Header
 */
char * getRequestAuthorization(const string *request) {
    char *toCmp = "Authorization: Basic ";
    char *ptr = NULL, *getCode = NULL;
    unsigned long posInReq = 0;
    unsigned short i = 0, j = 0;
    unsigned short len = 0;


    /* Tutorialspoint.com
     * This function returns a pointer to the first occurrence in haystack of any of
     * the entire sequence of characters specified in needle, or a null pointer if
     * the sequence is not present in haystack.
     */
    ptr = strstr(request->str, toCmp); // ptr zeigt nun an die Stelle von toCmp.
    if(ptr == NULL) {
        return NULL;
    }
    posInReq = ptr - request->str;
    posInReq += strlen(toCmp);
    i = (unsigned short)posInReq;


    // Ermittlung der Laenge des kodierten Teils.
    while(request->str[i] != '\x0d') {
        len++;
        i++;
    }
    getCode = calloc(len + 3, 1);
    if( getCode == NULL)
        exit(4);

    // Auslesen der Kodierung.
    for(j = 0; request->str[posInReq]  != '\x0d'; j++) {
        getCode[j] = request->str[posInReq];
        posInReq++;
    }
    getCode[j + 1] = '\0';

    return getCode;
}

/**
 * ließt aus einem char * Benutzername und Passwort
 * Hashed und base64 codiert diese dann auch gleich
 * @author pse1pg04
 * @param char *: data
 * @return unsigned String *: "Benutzername:Passwort" (Speicher muss später befreit werden)
 */
string * getPw(char * data){
    if (data == NULL)
        return NULL;
    int i = 0;
    char * sha = "{SHA}";
    size_t * outlen = calloc(2, sizeof(size_t)); // wird länge des Char * nach hashen und verschlüsselung enthalten
    if (outlen == NULL){
        exit(2); }
    while(data[i]!=':' && i<strlen(data)){
        i++;
    }
    if(i == strlen(data)){
        free(outlen);
        return NULL;
    }
    int j= i+1;
    while(data[j]!=':' && j<strlen(data)){
        j++;
    }

    if(j != strlen(data)){
        free(outlen);
        return NULL;
    }
    char * usr = calloc (i,2); // stellt Speicher Für den Username
    if (usr == NULL){
        exit(2);}
    for (int k = 0; k <= i; k++) {
        usr[k] = data[k];
    }
    i++;
    char * pasw = calloc(1,strlen(data)); // stellt Speicher für das PW
    if (pasw == NULL)
        exit(2);
    for(int j = 0; j+i <= strlen(data); j++){
        pasw[j] = data[i+j];
    }
    char * pasw2 = schickmachen(pasw, outlen); // hashed und verschlüsselt
    size_t gros = strlen(data)+ *outlen;
    string * dSatz = new_string(gros);
    int usrlen = strlen(usr);
    int l = 0;
    for (l; l <= usrlen ; l++) {
        dSatz->str[l] = usr[l];
    }
    usrlen = strlen(sha);
    l--;
    for (int f = 0; f <= usrlen ; f++) {
        dSatz->str[l] = sha[f];
        l++;
    }
    l--;
    usrlen = strlen(pasw2);
    for (int k = 0; k <= usrlen ; k++, l++) {
        dSatz->str[l] = pasw2[k];
    }                                           // schreibt den Benutzernamen und das PW in dSatz
    free(pasw2);
    free(usr);
    free(pasw);
    free(outlen);
    return  dSatz;
}
/**
 * Gibt Benutzername und Passwort mit printf über die Konsole aus
 * @author Tim Lause und Eric Wulfert
 * @param char* : B_P mit Benutzername und Passwort
 * @return void
 */
void B_P_ausgabe(char* B_P) {
    int i = 0;

    if (B_P == NULL)
        return;

    printf("%s", "\nBenutzername:");
    for (i; B_P[i] != ':' && i < strlen(B_P); ) {
        printf("%c", B_P[i]);
        i++;
    }
    printf("%s", "\nPasswort:");

    i++;

    for (i; i < strlen(B_P); i++) {
        printf("%c", B_P[i]);
    }
    printf("\n");

}

/** prüft ob eine zeile in einer datei mit dem 1.param übereinstimmt
 * @author Tim Lause
 * @param char*: passwort
 * @param char*: dateipfad zur htpasswd
 * @return int: 1=true 0=false
 */
int pswd_vergleich(char* passwort,char* dateipfad){
    FILE* htpasswd=fopen(dateipfad,"r+");
    if(htpasswd==NULL){
        printf("htpasswd not found!\n");
        exit(2);
    }

    fseek(htpasswd, 0, SEEK_END);
    int file_size = ftell(htpasswd);
    rewind(htpasswd);
    char c="0";
    int i=0,max_len=strlen(passwort),bool=0,file_pos=0;
    //Hauptschleife läuft bis zum ende der datei
    while(file_pos<file_size) {

        //Unterschleife prüft die zeilen
        for(i=0;i<max_len;i++){
            fscanf(htpasswd, "%c", &c);
            file_pos++;
            if(c!=passwort[i])
                bool++;
            if(c=='\n')
                break;
        }

        if(bool==0) {
            //alle Zeichen  stimmen überein
            fscanf(htpasswd, "%c", &c);
            file_pos++;
        }
        if (c=='\n'&&bool==0) {
            //Länge stimmt überein
            fclose(htpasswd);
            return 1;
        }
        bool=0;
    }
    //Hauptscheife durch Datei zuende
    fclose(htpasswd);
    return 0;
}