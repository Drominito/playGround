#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Einfach es sortieren:
// 1,4,6,10,200
//
// Dann wieder zurückschauen
// 4,200,1,10,6
// Beim Welchen Index ist es das kleinste?
// Ich wähle das erste Index des sortierten arrays und suche wo die Zahl in dem
// unsortieren Array ist...
// [0](1) -> [2](1)
//
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


int SearchNumInArray(int missed, int s, int* p) {
    for (int i = 0; i < s; i++) {
        if (p[i] == missed) { return i; }
    }
}

void sortArray(int s, int* a) {
    int min = 0;
    for (int it=0; it < s-1; it++) {
        for (int i = 0; i < s; i++) {
            if (a[i] > a[i+1]) {
              int tmp = a[i+1];
              a[i+1] = a[i];
              a[i] = tmp;
            }
        }
    }
}

int spectrumIndex(int s, int* arr, int offset) {
    int ref[s]; memcpy(ref, arr, sizeof(int)*s));
    sortArray(s, ref);
    int o = MIN(s-1, offset);
    return SearchNumInArray(ref[o], s, arr);
}



int main() {

    const int s = 5;
    int offset = 0;
    int arr[s] = { 4, 200, 1, 10, 6 };
    int index = spectrumIndex(s, arr, offset);
    printf("\n\nmin(-%d) -> arr[%d]=%d\n", offset, index, arr[index]);


}
