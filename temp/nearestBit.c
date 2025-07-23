#include <stdio.h>
#include <math.h>
#include <stdint.h>

int nearest_low_power_of_two(float u) {
    if (u < 1.0f) return 0;
    return 1 << (int)floorf(log2f(u));
}

int main() {
    uint16_t c = 0b000000001111; // Beispiel: 2
    uint16_t expected = 0b0100000000000; // Erwarte 2 an die MSB-Position geschoben

    int msb = nearest_low_power_of_two(c);
    int offset = (msb - 1);
    uint16_t rotated = c << (sizeof(c) * 8 - offset);

    printf("Rotated: %u | Expected: %u\n", rotated, expected);
    printf("DEBUG: Nearest lower power of two for %d = %d\n", c, msb);

    return 0;
}

