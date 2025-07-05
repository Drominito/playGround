#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** maloco(char* str, char* str2) {

    
    char** buff = NULL;
    buff = malloc(2*sizeof(char*));
    for (int i = 0; i < 2; i++) {
        buff[i] = malloc(16);
    }
    
    for (int i = 0; i < strlen(str); i++) {
        buff[0][i] = str[i];
    }
    for (int i = 0; i < strlen(str2); i++) {
        buff[1][i] = str2[i];
    }
    return buff;
    
}


int main() {

    char str[] = "Hello";
    char str2[] = "Back!";

    char** txt = NULL;
    txt=maloco(str, str2);
    printf("%s %s", txt[0], txt[1]);
    free(txt);



    return 0;
}
