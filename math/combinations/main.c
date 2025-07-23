#include <stdio.h>
#include <math.h>


int main() {
   // easiest example a + b = c
   // here for now a + b = 10

   // more harder = a + b + c = 180
   // simpler problem a + b +c = 9

   //int char[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
   //int amount = 2 // damn c dont have code generation
   // 2
   int result=180;
   int equals=0;
   double it_needed=result*result*result;

   for (int a = 1; a <= result; a++) {
       for (int b = 1; b <= result; b++) {
              int c = result - a - b;
              if (a+b+c==result && c > 0) {
                   printf("%d + %d + %d = %d | %dth combination\n", a, b, c, result, equals++);
              }

        }
   }
   printf("\na+b+c=180 have %d combination.\nIterations needed: %.2lf\n", equals, it_needed);
   printf("This naive approach is %d-Times slower than the acutal combination count\n", (int)it_needed/equals);

   return 0;
}
