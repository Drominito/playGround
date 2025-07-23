#include <stdio.h>
#include <stdlib.h>

#define sz 10 // im too lazy to give an input how big they should be.
#define MAX_DUPLICATE_DEPTH 16
#define zofi sizeof(int)


struct list {
    int** arr;
    int duplicates;
};

int main(int argc, char* argv[]) {

    // currently only 1 Parameter availible
    if (argc != 2) { return 1; }
    int count = atoi(argv[1]);
    int* arr = (int*)malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        arr[i] = rand() % sz;
        printf("%i: %i\n", i, arr[i]);
    }


    // Example(Line, Number):
    // 0: 34
    // 1: 34
    // 2: 4
    // 3: 5
    // 3: 4
    // 4: 2
    // 5: 4
    // 6: 34
    // -- --
    //(Raw)
    // [02]: ^= 1 (0 Duplicates) 
    // [04]: ^= 2 (1 Duplicates) Lines:[2, 4]
    // [05]: ^= 1 (0 Duplicates)
    // [34]: ^= 2 (2 Duplicates) Lines [0, 1, 6]

    // (Only with duplicates)
    // [34]: ^= 2 (2 Duplicates) Lines [0, 1, 6]
    // [04]: ^= 2 (1 Duplicates) Lines:[2, 4]




    // concept: j(second) go through all an compares with i(first)
    // currently it cannot join more than 2 duplicates at once.

    // 2D heap array (with max 16 Duplicates)
    struct list = {}; list.arr = {}; list.duplicates = 0;

   
    list.arr = (int**)malloc(count * zofi);
    for (int i = 0; i < MAX_DUPLICATE_DEPTH; i++) { 
        list.arr[i] = (int*)malloc(count * zofi);
    }


   // maybe just grab all 2D lines with the same connection,
   // convert it to 1D array and then delete unnecessairly duplicates?

   // maybe add this as an (key<->value)-struct?


   // or -> i start with (e.g.:4), then sub loop to for each every array for other '4's. And then next..
   for (int i = 0; i < count; i++) {
        for (int j = 0; j < count i++) {


        }
   }

   
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
        //i and j may not be the same->will compair itself
            if (i != j && arr[i] == arr[j]) {
                list.duplicates++; // the actual is always the half.
                list.arr
                
                printf("Duplicate found on lines: %i & %i\n", i, j);
            }
        }
    }

    // output should be an normal array(user-input) of number: count of it
    // then it can sort out, by exclude an array which contains 1(no duplicates)



    printf("\nTotal Duplicates: %i\n", dup);
    return 0;
}
