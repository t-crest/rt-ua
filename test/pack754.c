#include <stdio.h>
#include <string.h>
#include <stdint.h>


void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
    printf("\n");
}

/* Handling of IEEE754 floating point values was taken from Beej's Guide to
 * Network Programming (http://beej.us/guide/bgnet/) and enhanced to cover the
 * edge cases +/-0, +/-inf and nan. */
static uint64_t
pack754(long double f, unsigned bits, unsigned expbits) {
    unsigned significandbits = bits - expbits - 1;
    long double fnorm;
    long long sign;
    if(f < 0) { sign = 1; fnorm = -f; }
    else { sign = 0; fnorm = f; }
    int shift = 0;
    while(fnorm >= 2.0) { fnorm /= 2.0; ++shift; }
    while(fnorm < 1.0) { fnorm *= 2.0; --shift; }
    fnorm = fnorm - 1.0;
    long long significand = (long long)(fnorm * ((float)(1LL<<significandbits) + 0.5f));
    long long exponent = shift + ((1<<(expbits-1)) - 1);
    return (uint64_t)((sign<<(bits-1)) | (exponent<<(bits-expbits-1)) | significand);
}

static uint64_t
copy_pack754(long double f, unsigned bits, unsigned expbits) {
    unsigned char *b = (unsigned char*) &f;

    b[0]=0xf0;
    b[1]=0x0f;
    return (uint64_t)*b;
}

int main(int argc, char *argv[])
{
    float f_value;
    double d_value;
    uint64_t f_value_pack754, d_value_pack754;
    uint64_t f_copy, d_copy;

    d_value = f_value = 128798798.796173687123;

    f_value_pack754 = pack754(f_value, 32, 8);
    d_value_pack754 = pack754(d_value, 64, 11);

    printf("Float Bits:\n\t");
    printBits(sizeof(float), (void*)&f_value);
    printf("Float pack754 Bits:\n\t");
    printBits(sizeof(uint64_t), (void*)&f_value_pack754);

    printf("Double Bits:\n\t");
    printBits(sizeof(double), (void*)&d_value);
    printf("Double pack754 Bits:\n\t");
    printBits(sizeof(uint64_t), (void*)&d_value_pack754);

    return 0;
}
