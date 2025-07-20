#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>


// funktioniert nur in einem kontext. Fürs erste soll es dafür reichen.
#define mkalias(x, y) char* x = y
// Ich dachte mir etwas mit macros zu machen, aber dann bin ich auf va_args
// gekommen. Sonst wäres es noch komplizierter.
#define strlenv(x) j

#define MAX(x, y)  (((x) > (y)) ? (x) : (y))

struct Sarr {
    char arr[];
};


// maybe for later
struct Array {
    int object_s;
    int len_t;
    char arr[];
};


int getMax(char* arr[]) {
    int i = 0;
    while (arr[i] != NULL) { i++; }
    return i;
}

int getLen(char* arr[]) {
    int amnt = getMax(arr);
    int total_len = 0;
    for (int i = 0; i < amnt; i++)
        total_len += strlen(arr[i]);

    return total_len;
}

char* string_concat(const char* fmt, ...) {
    va_list args;
    va_list args_copy;
    va_start(args, fmt);
    va_copy (args_copy, args);

    // remove the first arg
    //char* dummy = va_arg(args, const char*);
    char* dummy_cp = va_arg(args_copy, const char*);


    int s=0;
    char* current_arg;
    while ( (current_arg = va_arg(args_copy, const char*)) != NULL ) {
        s += strlen(current_arg);
    }

    char* r = malloc(s);
    s = 0;
    while ( (current_arg = va_arg(args, const char*)) != NULL ) {
        memcpy(r+s, current_arg, strlen(current_arg));
        s += strlen(current_arg);
    }

    va_end(args);
    va_end(args_copy);
    return r;
}

void s_string_concat(char* buff, char* data[]) {
    int amnt = getMax(data);
    int o = 0;
    for (int j = 0; j < amnt; j++) {
        memcpy(buff+o, data[j], strlen(data[j]));
        o += strlen(data[j]);
    }
}


void stack_main_combinate() {
    char* arr[] = {"Hallo, ", "Welt", "My!", NULL};
    char* buff = alloca(getLen(arr));
    s_string_concat(buff, arr);
    // make an alias result->buff like as an refrence with macros?
    mkalias(result, buff);
    printf("\n%s\n", result); // → "Hallo, Welt!"

}

void heap_main_combinate() {
    char* result = string_concat(NULL, "Hallo, ", "Welt!", "My!", NULL);
    printf("%s\n", result); // → "Hallo, Welt!"
    free(result);
    // das erste Argument muss wegen va_args null sein. Aber verbesserungsfähig.
}

int int_strdiff(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    return abs(len_a - len_b);
    // if it's return 0, there are no changes needed.
}

void string_replace(char* buff,
    const char* str, const char* target, const char* replacement) {

    int s = strlen(str);

    // the amount of targets can't be bigger than the size of the string
    // For simplicity, i take the half.
    char target_s[s/2];
    int count = 0;
    
    for (int i = 0; i < s; i++) {
        if (str[i] == target)
            target_s[count++] = i;
    }

    
    // Prove that I'm overthinking:

    // My first approach is to split strings between the target's.
    // If the target is more than one char,
    // then it will check iteratively each char e.g:
    // R - Ru - Rus - Rust
    //
    // everything is a target   -> 0 pieces
    // every second(2) is a target -> (s/2) pieces
    // every x is a target -> (s/x) pieces
    // xxRustxxxRustxxxxRustxxxRust
    // -> 8 pieces -> 8-1 cut-lines
    
    // Second thought is that the string will only be splitten after the target.

    // difference between split everything at once, and step by step?
    // I'll try the second first.

    // how now I imagine the process:
    // Ich mag C, weil C schnell ist.
    // Ich mag C<,> weil C schnell ist. // target_s[0]+1
    // Ich mag C<,>
    // Now due to the string-amount with more > 1 , the indecies are no longer valid
    // So -> calculate the diff between the *replacement* and *target*
    // Ich mag Rust<,> // stringdiff("Rust"-"C") -> 3
    // So -> set all indecies target_s[1..x] to +3


}

int main() {

    const char* input = "Ich mag C, weil C schnell ist.";
    char* buff = alloca(getLen(input));
    string_replace(buff, input, "C", "Rust");
    mkalias(result, buff);
    printf("\n%s\n", result);
        
}
