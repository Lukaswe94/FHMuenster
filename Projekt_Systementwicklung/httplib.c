#include <assert.h>
#include "httplib.h"
#include <ctype.h>
#include <unistd.h>

#include "error_handeling.h"


/**
 * Hängt eine source mit der Länge len an einen destination String
 * @param string *: dest
 * @param const char *: src
 * @param size_t: len mit der länge von src
 * @author pse1pg03
 * @return string*: ein String mit neuer Länge und der source angehängt
 */
string *str_cat(string *dest, const char *src, size_t len) {
    if(dest->str == NULL || src == NULL)
        return NULL;

    dest->str = realloc(dest->str, (dest->pos + 1 + len) * 2);
    if (dest->str == NULL) {
        exit(4);
    }
    memcpy((dest->str + dest->pos + 1), src, len);
    dest->pos = dest->pos + len;
    dest->len = 2 * (dest->pos + 1);
    return dest;
}
/**
 * erstellt eine neue struct String * mit der Länge len
 * @param size_t: len
 * @author Sebastian Schinzel
 * @return string*: pointer auf den neuen string
 */
string *new_string(size_t len) {
    string *str = calloc(sizeof(string), 1);
    if (str == NULL) {
        exit(2);
    }

    str->str = calloc(2, len);
    if (str->str == NULL) {
        exit(3);
    }

    str->len = len * 2;
    str->pos = 0;

    return str;
}

/**
 * Kopiert eine source in einen neu erstellten string *
 * @param const char *: src
 * @param size_t: len
 * @author Sebastian Schinzel
 * @return string*: pointer auf den neuen string
 */
string *cpy_str(const char *src, size_t len) {

    string *dest = new_string(len +1); // +1 falls len == 0 ist
    memcpy(dest->str, src, len);
    dest->pos = len - 1;

    return dest;
}
/**
 * Befreit den Speicher eines Strings
 * @param string * str
 * @author Sebastian Schinzel
 * @return void
 */
void free_str(string *str) {
    if(str != NULL) {
        assert(str != NULL);
        assert(str->str != NULL);
        free(str->str);
        free(str);
    }
}
/**
 * Gibt die länge des char * im string zurück
 * @param string * str
 * @author Sebastian Schinzel
 * @return size_t pos
 */
size_t get_length(string *str) {
    assert(str != NULL);
    return str->pos + 1;
}
/**
 * Gibt den char * im string zurück
 * @param string *: str
 * @author Sebastian Schinzel
 * @return char *: Der Inhalt des strings
 */
char *get_char_str(string *str) {
    assert(str != NULL);
    return str->str;
}

/**
 * Macht aus Großbuchstaben in einem char* Kleinbuchstaben
 * @param string *: src
 * @author pse1pg03
 * @return char *: src->str mit nur kleinbuchstaben
 */
char *lower(string *src) {
    int i;
    for (i = 0; i <= src->pos; i++) {
        src->str[i] = (char) tolower(src->str[i]);
    }
    return src->str;
}


/**
 * Dec wert vom Ascii zeichen nehmen und umrechnen, damit man den dec wert der Stelle erhält
 * @param char: c, das Zeichen welches es zu ersetzen gilt
 * @return int: Nummer des Zeichens in der ASCII Tabelle
 */
int hexToInt(char c) {
    if (c >= 97)
        c = c - 32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
}
/**
 * Umwandlung zweistelliger Hex-zahlen in den Dezimalwert des Ascii zeichens
 * @param char: c, erste Stelle der Hex-zahl
 * @param char: d, zweite Stelle der Hex-zahl
 * @return int: Bsp. für hex 20 return = 32 und (char) 32 ist ' '
 */
int hexToAscii(char c, char d) {
    int high = hexToInt(c) * 16;
    int low = hexToInt(d);
    return high + low;
}
/**
 * Funktion die die Source solange durchsucht nach zu ersetzenden zweistelligen hex-werten bis keine mehr vorhanden sind
 * @param string*: src, die quelle in der möglicherweise hex-zeichen vorkommen
 * @return string*: die source mit ersetzten zeichen oder wenn keine Zeichen vorkommen nur die src
 */
string *hexReplace(string *src) {
    char *start;
    size_t len = 0;
    char replace;
    string *dest;
    start = memchr(src->str, '%', src->pos );     // suche nach einem '%' in der Resource, das anzeigt das ein hexwert für ein Ascii zeichen kommt

    if (start == NULL) {
        return src;
    }
    len = src->pos - strlen(start);     // letzte stelle vor dem '%'
    replace = (char) hexToAscii(start[1],start[2]);    // Ascii - Zeichen für den hex-Wert erhalten, alle Ascii zeichen haben nur 2 Ziffern als Hex-Werte
    src->str[len + 1] = replace;    // hex-Wert durch Ascii-Zeichen ersetze
    dest = new_string(src->pos -2);
    dest->str = memcpy(dest->str, src->str, len+2);
    dest->pos = len+1;
    memcpy((dest->str+len+2), start+3, strlen(start)-3);
    dest->pos = src->pos -2;

    while(start != NULL){
        start = memchr(dest->str, '%', dest->pos );
        dest = hexReplace(dest);
    }
    free_str(src);
    return dest;
}





