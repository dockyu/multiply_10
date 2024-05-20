#include <stdio.h>

void print_binary(unsigned int value) {
    printf("\t");
    int i;
    for (i = 31; i >= 0; i--) {
        printf("%u", (value >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

// Return x * 10
float float_mul10(float x)
{
    // using bitwise operation; No mul/div

    // printf("(unsigned)x\n");
    // printf("\t%u\n", (unsigned)x);
    // printf("\t0x%08x\n", (unsigned)x);
    // print_binary((unsigned)x);

    unsigned* p = (unsigned*)&x;

    // printf("*p\n");
    // printf("\t0x%08x\n", *p);
    // print_binary(*p);

    unsigned sign = (*p & 0x80000000) >> 31; /* 1000 0000 0000 0000 0000 0000 0000 0000 */
    unsigned exp = (*p & 0x7F800000) >> 23;  /* 0111 1111 1000 0000 0000 0000 0000 0000 */
    unsigned frac = *p & 0x007FFFFF;         /* 0000 0000 0111 1111 1111 1111 1111 1111 */

    // printf("sign\n");
    // printf("\t0x%08x\n", sign);
    // print_binary(sign);
    // printf("exp\n");
    // printf("\t0x%08x\n", exp);
    // print_binary(exp);
    // printf("frac\n");
    // printf("\t0x%08x\n", frac);
    // print_binary(frac);

    frac = frac | 0x00800000;
    // printf("frac with implicit leading bit 1\n");
    // printf("\t0x%08x\n", frac);
    // print_binary(frac);

    unsigned frac2 = frac << 1; /* frac * 2 */
    unsigned frac8 = frac << 3; /* frac * 8 */

    // printf("frac * 2\n");
    // printf("\t0x%08x\n", frac2);
    // print_binary(frac2);

    // printf("frac * 8\n");
    // printf("\t0x%08x\n", frac8);
    // print_binary(frac8);

    frac = frac2 + frac8; /* frac * 10 */
    // printf("frac * 10\n");
    // printf("\t0x%08x\n", frac);
    // print_binary(frac);

    // if (frac >> 27) {
    //     exp += 4;
    //     frac = frac >> 4;
    // } else {
    //     exp += 3;
    //     frac = frac >> 3;
    // }

    int shift = 3 + (frac >> 27);
    exp += shift;
    frac = frac >> shift;
   
    frac = frac & 0xff7fffff; /* 1111 1111 0111 1111 1111 1111 1111 1111 */

    // printf("frac 23 bit\n");
    // printf("\t0x%08x\n", frac);
    // print_binary(frac);

    float result;
    unsigned* rp = (unsigned*)&result;

    *rp = (sign << 31) | (exp << 23) | frac;

    return result;
}

int main()
{
    float x = 4.9;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    x = 4.91;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    x = 4.92;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    x = 99.0;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    x = 99.9;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    x = 3.14;
    printf("x:%f\n", x);
    printf("%f\n", x*10);
    printf("%f\n\n", float_mul10(x));

    // float_mul10(x);
    return 0;
}
