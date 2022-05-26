//
// Created by pseuser on 16.06.20.
//

#include "file_handeling.h"
/**
 * Funktion die aus der Resource eine Datei öffnet und den Inhalt ausgibt
 * @param char *: fname, Name der Datei
 * @author pse1pg03
 * @return char*: die Datei im Ziel-string*
 */
string *fileTobody(char *fname) {
    FILE *f = fopen(fname, "rb"); // Öffnen der Datei die in der Resource angegeben wurde bsp. index.html

    long siz = 0;
    if (f == NULL) {

        chdir("../../");
        return NULL; //falls das öffnen der datei nicht geklappt hat
    }

    fseek(f, 0, SEEK_END); // Position an das Ende der Datei
    siz = ftell(f);     // Durch Position am Ende der Datei können wir der variable siz die Größe der Datei mitteilen
    fseek(f, 0, SEEK_SET);  //Position wieder zum Anfang
    string *dest = new_string(siz);
    if (dest) {
        fread(dest->str, 1, siz, f);    // Einlesen der Datei in den Body
        dest->pos = siz - 1;
    }

    fclose(f);  //Datei schließen und body zurückgeben
    chdir("../../");

    if(dest->pos > 100000000000000000) // für den komischen fall, dass pos unglaublich groß wird
        dest->pos = 0;

    return dest;
}