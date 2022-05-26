//
// Created by pseuser on 16.05.20.
//

#include "base64.h"
#include <stdint.h>
#include <stdlib.h>
#include "httplib.h"
#include "error_handeling.h"



static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};
/**
 * erstellt ein decoding table aus dem Vorhandenen encoding table
 * @param
 * @author Sebastian Schinzel
 * @return
 */
void build_decoding_table1() {

    int i;
    decoding_table = malloc(256);

    for (i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}


/**
 * Verschlüsselt einen char* nach dem base64 Verfahren
 * @param const unsigned char *: data, mit dem zu verschlüsselden Datensatz
 * @param size_t: input_length, mit der länge von data
 * @param size_t *: output_length, dem die neue länge des returns zugewiesen wird
 * @author Sebastian Schinzel
 * @return char *: mit dem nun verschlüsselten Inhalt von data
 */
char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {

    int i,j;
    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';
    encoded_data[*output_length] = '\0';

    return encoded_data;
}

/**
 * Entschlüsselt einen char* nach dem base64 Verfahren
 * @param const unsigned char *: data, mit dem zu entschlüsselden Datensatz
 * @param size_t : input_length mit der länge von data
 *        (muss %4 teilbar sein!)
 * @param size_t *: output_length dem die neue länge des returns zugewiesen wird
 * @author Sebastian Schinzel
 * @return char*: Entschlüsselter Inhalt von data
 */
unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length) {

    int i, j;
    if (decoding_table == NULL) build_decoding_table1();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = malloc(*output_length + 1);
    if (decoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
                          + (sextet_b << 2 * 6)
                          + (sextet_c << 1 * 6)
                          + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    decoded_data[*output_length] = '\0';

    return decoded_data;
}


/**
 * Befreit den Speicher vom decoding table
 * @author Sebastian Schinzel
 * @return void
 */
void base64_cleanup() {
    free(decoding_table);
}

/**
 * Wrapper Funktion für base64_decode.
 * Baut und schließt den decoding table und ermittelt die in_len
 * @param unsigned char *: data
 * @param size_t *: out_len, in den die Neue länge von data geschrieben wird
 * @return unsigned char*: data entschlüsselt (Speicher muss später befreit werden)
 */
unsigned char * entschlusseln(unsigned char * data, size_t * out_len){


    build_decoding_table1();
    unsigned char * zuruck;

    zuruck = base64_decode(data, strlen(data),out_len); // gibt ein Speicher(malloc) zurück mit der codierung

    base64_cleanup();   // befreit den coding table
    return zuruck;
}
/**
 * Wrapper Funktion für base64_enccode
 * fängt leere char * data ab
 * @param unsigned char *: data
 * @param size_t *: out_len, in den die Neue länge von data geschrieben wird
 * @return char *: data Verschlüsselt(Speicher muss später befreit werden)
 */
char * verschlusseln(unsigned char * data, size_t * out_len){
    if ( data == NULL)  //
        return NULL;

    char * zuruck;

    zuruck = base64_encode(data, SHA_DIGEST_LENGTH,out_len); // da wir nur hashed werte verschlüsseln bietet es sich hier an einen festen wert zu nehmen
    // zuruck enthält speicher(mit malloc) mit der verschlüsselten rückgabe

    return zuruck;
}

/**
 * Hashed und base64 decodiert den Ihnalt von data
 *
 * @param char *: data (darf nicht NULL sein)
 * @return unsigned char *: Hashed und codierter Inhalt von data (Speicher muss später befreit werden)
 */
char * schickmachen(unsigned char * data, size_t * out_len){

    size_t grose = strlen(data);
    unsigned char * hash = calloc(100, SHA_DIGEST_LENGTH);    // Der Hashed wert kann hat immer eine länge von 20 byte
    if (hash == NULL)
        exit(2);
    SHA1((const unsigned char *)data, grose, hash);

    char * tausch = verschlusseln(hash, out_len);

    free(hash);
    return tausch;
}

