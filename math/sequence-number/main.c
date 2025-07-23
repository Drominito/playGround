#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// (5, 7, 9, ? , 13)    5 + x       -> y = 2x + 5



#define MAX_ARR_SIZE 8
typedef struct carr {
 int amnt;
 int mindex;
 int* arr;
} carr;


int getrndarray(int maxsize, int amount) {
 // example: (5, 8, 12, 20, 36, ..)
 return 0;
}


int x_linear_sequence(carr a) {
  // it's only linear here.
  // just checking the first 2 
  int steps = a.arr[1] - a.arr[0];
  return a.arr[a.mindex] = a.arr[a.mindex-1] + steps;
}



int main(int argc, char* argv[]) {
   carr a;
   a = (carr) {.amnt = 5, .mindex = 3};
   a.arr = (int[]){ 8, 10, 12, 0, 16 };
   
   int result = x_linear_sequence(a);
   printf("the result is %d\n", result);
   printf("the full array:\n");

   for (int i = 0; i < a.amnt; i++) {
      printf("a.arr[%d] = %d\n", i, a.arr[i]);
   } return 0;
   
}
