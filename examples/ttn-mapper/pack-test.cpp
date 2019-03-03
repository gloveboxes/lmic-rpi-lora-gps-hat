// gcc -o pack-test pack-test.cpp -lm
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

int main() {

uint8_t coords[6];
int32_t lat = -34.1234 * -10000;
int32_t lon = 151.1234 * 10000;
int alt = 12;
int tdop = 123;

// Pad 2 int32_t to 6 8uint_t, skipping the last byte (x >> 24)
coords[0] = lat;
coords[1] = lat >> 8;
coords[2] = lat >> 16;

coords[3] = lon;
coords[4] = lon >> 8;
coords[5] = lon >> 16;

coords[6] = alt;

coords[7] = tdop;
for (int i = 0; i < 8; i++)
{
    printf("%02X", coords[i]);
}
printf("\n");
}
