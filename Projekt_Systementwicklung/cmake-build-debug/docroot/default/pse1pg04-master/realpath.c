#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#define DOC_ROOT "/home/pseuser/ssc/test2"
// /Users/ssc/Desktop/test1   | existiert
// /Users/ssc/Desktop/test2   | existiert
// /Users/ssc/Desktop/test2/a | existiert nicht
// /Users/ssc/Desktop/test3   | existiert nicht

int test(char* test) {
    char *ptr = realpath(test, NULL);

    if(ptr == NULL) {
        // Der Pfad existiert nicht, aber liegt er wenigstens im DocRoot?
        char *old = calloc(1, PATH_MAX);
        if(old == NULL)
            exit(1);

        realpath(test, old);
        if(strncmp(DOC_ROOT, old, strlen(DOC_ROOT)) == 0) {
            printf("ist im DocRoot       | existiert nicht\n");
        } else {
            printf("ist nicht im DocRoot | existiert nicht\n");
        }
    } else {
        // Der Pfad existiert, aber liegt er im DocRoot?
        if(strncmp(DOC_ROOT, ptr, strlen(DOC_ROOT)) == 0) {
            printf("ist im DocRoot       | existiert\n");
        } else {
            printf("ist nicht im DocRoot | existiert\n");
        }
    }

    return 0;

}

int main() {
    test("/home/pseuser/ssc/test2/../test2/a"); // ist im DocRoot       | existiert nicht
    test("/home/pseuser/ssc/test2/../test3");   // ist nicht im DocRoot | existiert nicht
    test("/home/pseuser/ssc/test1/../test2");   // ist im DocRoot       | existiert
    test("/home/pseuser/ssc/test1/../test1");   // ist nicht im DocRoot | existiert
    return 0;
}
