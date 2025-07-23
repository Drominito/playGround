#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdint.h> // memcpy

int main() {
    int sz=sizeof(int[4]); // 16 bytes -> 128bits -> 2*64
    int* ptr = malloc(sz);
    
    uint64_t a = 32, b = 64;
    uint64_t numbsz = sizeof(a); // 8
    //memcpy(ptr, &a, numbsz); // if 3-arg is to big -> core dumped (similar to seg faults?)
    //memcpy(&ptr[2], &b, numbsz); // same as ptr+sizeof(int[2]
    

    // read it byte by byte.



    char buff[sz];
    memcpy(buff, ptr, sz);

    for (int i = 0; i < sizeof(uint64_t); i++) {
        buff[i] = (a << i*8) & 0xaa;
    }

    for (int i = 0; i < sz; i++) {
        printf("ptr[%d]=%d\n", i, buff[i]);
    }
    return 0;
}
