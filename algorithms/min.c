#include <stdio.h>

int getMinArr(int s, int* p) {
    int min = *p;
    for (int i = 0; i < s; i++) {
        if (p[i] < min) {
            min = p[i];
        }
    } return min;
}

int main() {
    int a[] = { 16, 5, 8, 10, 8, 2, 80, 3, 1, 10};
    int s = sizeof(a)/sizeof(*a);
    printf("min: %d\n", getMinArr(s, a));

}
