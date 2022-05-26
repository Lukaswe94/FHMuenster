#include <assert.h>
#include "httplib.h"




/** Funktion fügt ein char* an einen string an
 *
 * @param str - an dem angehängt werden soll ,char* der angehängt wird ,länge der src
 * @return angehängten string
 */
string* str_cat(string* dest, const char* src,int len) {
    int i;

    //Überprüfung ob neuer Speicher nötig ist
    if(dest->len-dest->pos<len){
        dest->str= realloc(dest->str, len + dest->len+6);
        //realloc überprüfen
        if (dest->str == NULL) {
            printf("error in str_cat/nreallow failed");
            exit(2);
        }
        //len auf die Größe des neuen Speichers
        dest->len=dest->len+len;
    }

    int r=dest->pos;

    for(i=0;i<(len);i++) {
        dest->str[r+i] = src[i];
    }
    //pos entspricht der Anzahl aller Zeichen
    dest->pos=dest->pos+len;
    return dest;
}
string* new_string(size_t len) {
    string* str = calloc(sizeof(string), 1);
    if(str == NULL) {
        exit(2);
    }

    str->str = calloc(len, 2);
    if(str->str == NULL) {
        exit(3);
    }

    str->len = len * 2;
    str->pos = 0;

    return str;
}

void print_string(string* str) {
    for(int i=0; i < str->pos; i++) {
        putchar(str->str[i]);
    }
}

string* cpy_str(const char* src, size_t len) {
    string* dest = new_string(len);
    memcpy(dest->str, src, len);
    dest->pos=len-1;

    return dest;
}

void free_str(string* str) {
    assert(str != NULL);
    assert(str->str != NULL);

    free(str->str);

    free(str);
}

size_t get_length(string* str) {
    assert(str != NULL);
    return str->pos ;
}

char* get_char_str(string* str) {
    assert(str != NULL);
    return str->str;
}
/** Funktion ersetzt alle kleingeschrieben Buchstaben von bis
 *
 * @param str,von,bis

 */
void case_dont_matter(string* str,int from,int to) {
    //toupper von bis
    int ascii;

    for(from=from;from<to;from++){
        ascii=str->str[from];
        if(ascii>96&&ascii<123) {

            str->str[from]=(char)(ascii-32);
        }

    }
}
/** Funktion ersetzt alle kleingeschrieben Buchstaben
 *
 * @param str

 */
void case_dont_matter_at_all(string* str) {
    //toupper für ganzen str
    int ascii,i;

    for(i=0;i<str->pos;i++){
        ascii=str->str[i];
        if(ascii>96&&ascii<123) {

            str->str[i]=(char)(ascii-32);
        }

    }
}

string* rewrite(string* dest,char* new_str,int pos){
  int i=0;
    if(dest->len<pos)
        realloc(dest->str,pos+2);
    if (dest->str == NULL) {
        printf("error in str_cat/nreallow failed");
        exit(2);
    }
    for(i;i<pos;i++) {
        dest->str[i] = new_str[i];
    }
    dest->pos=i;

    for(i;i<dest->len;i++){
        dest->str[i]='\0';

    }
    return dest;
}
