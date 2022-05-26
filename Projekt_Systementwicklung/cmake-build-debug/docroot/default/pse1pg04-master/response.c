#include "httplib.h"
#include "response.h"


/** Funktion liest eine datei aus
 *
 * @param char*- absoluter pfad zur datei
 * @return inhalt der datei
 */
char* getFile(char* adresse)
{   unsigned int len;
    char* inhalt;
    char c;
    int i=0;

    if (adresse=="")
        return NULL;

    FILE* fp=fopen(adresse,"r+");
    if(fp==NULL){
        printf("file not found");
        return NULL;
    }
    //länge der datei ermitelln
    fseek(fp,0L,SEEK_END);
    len=ftell(fp);
    if(len==0)
        return NULL;
    rewind(fp);
    inhalt=calloc(len+1,1);
    if(  inhalt== NULL){
        exit(2);
    }

    //inhalt der datei auslesen und in inhalt scheiben
    for(i=0;i<len;i++){
        fscanf(fp,"%c",&c);
        inhalt[i]=c;
    }
    fclose(fp);



    return inhalt;

}
/** Funktion liest die länge einer datei
 *
 * @param char*- absoluter pfad zur datei
 * @return int länge der datei
 */
int getFilelen(char* adresse) {
    unsigned int len;


    FILE *fp = fopen(adresse, "r");
    if (fp == NULL) {
        printf("file not found");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    len = ftell(fp);
    return len;
}



char* getContenttype( string* URL){
    int i=0,j=0;
    char* content;
    char* type;
    if (URL->str==NULL){
        return "Content-Type:application/data\r\n\r\n";
    }

    while (URL->str[i]!='.' && i<URL->pos){
        i++;
        //i index auf die Stelle vor dem Punkt vor dem Datentypen
    }

    content=calloc((URL->pos+1-i),1);
    if(content==NULL){
        printf("calloc Fehler");
        exit(2);
    }
    //datentype in content schreiben
    for(i+2;i<=URL->pos;i++,j++){
        content[j]=URL->str[i];

    }

    if(strncmp(content,".html", 5)==0){
        free(content);
        return "Content-Type:text/html\r\n\r\n";}
    else if(strncasecmp(content,".png",4)==0){
        free(content);
        return "Content-Type:image/png\r\n\r\n";}
    else if(strncmp(content,".jpg",4)==0){
        free(content);
        return "Content-Type:image/jpg\r\n\r\n";}
    else if(strncmp(content,".js",3)==0){
        free(content);
        return "Content-Type:application/javascript\r\n\r\n";}
    else{
        free(content);
        return "Content-Type:application/data\r\n\r\n";}
}
/** Funktion wandelt int in ein char*
 *
 * @param int nummer
 * @return char* zahl als char*
 */
char* inttoStr(int num ){

    char c;
    int ziffer=num,potenz,i=0,zehnerpotenz=0;;
    //anzahl der stellen ermitteln z.B 5780 5*10³
    while(ziffer>10){
        ziffer=ziffer/10;
        zehnerpotenz++;
    }
    //ziffer entspricht der 1. ziffen z.B 5
    char* str=calloc(zehnerpotenz+2,1);
    if (str==NULL){
        exit (1);
    }

    for(i;i<=zehnerpotenz;i++) {

        c=(char)('0'+ziffer);
        str[i] = c;
        potenz=mathpunkthpow_willnichtfunktioniren(10,zehnerpotenz-i);
        //die ziffer mal die zehnerpotenz von der num abziehen zB 5780-5000
        num=num-ziffer*potenz;
        ziffer=num;
        //nächste ziffer ermitteln
        while(ziffer>10){
            ziffer=ziffer/10;
        }
    }
    str[zehnerpotenz+1] ='\0';

    return str;
}
int mathpunkthpow_willnichtfunktioniren(int base, int exp){
    //math.h führte zu  fehlern
    //int version von pow(double,double)
    int i,erg=1;
    for(i=0;i<exp;i++){
        erg=erg*base;
    }
    return erg;
}