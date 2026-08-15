  /* Davi_Rangel 2411930 3WB */
  /* Victor_Hugo_Brito 2421278 3WB */

#include <stdio.h>
#include "bigint.h"

void exibe_bigint(BigInt n, long val){
    printf("| resultado: ");
    for (int i = 0; i < 16; i++){
        printf("%.2x ", n[i]);
    }
    printf("\n");
}

int main(void){
    // teste big_val
    printf("teste big_val\n");
    long val;
    BigInt a, b, c;
    BigInt a_invertido;
    
    // bigint 1
    val = 1;
    printf("val: %ld\t", val);
    big_val(a, val);
    exibe_bigint(a, val);

    // bigint -1
    val = -1;
    printf("val: %ld\t", val);
    big_val(a, val);
    exibe_bigint(a, val);

    // bigint 512
    val = 512;
    printf("val: %ld\t", val);
    big_val(a, val);
    exibe_bigint(a, val);

    // teste big_comp2
    printf("\nteste big_comp2\n");
    // bigint 1
    val = 1;
    printf("val: %ld\t", val);
    big_val(a, val);
    big_comp2(a_invertido, a);
    exibe_bigint(a_invertido, val);

    // bigint -1
    val = -1;
    printf("val: %ld\t", val);
    big_val(a, val);
    big_comp2(a_invertido, a);
    exibe_bigint(a_invertido, val);

    // bigint 0
    val = 0;
    printf("val: %ld\t", val);
    big_val(a, val);
    big_comp2(a_invertido, a);
    exibe_bigint(a_invertido, val);
    
    // teste big_sum
    printf("\nteste big_sum\n");
    // bigint 1 + 1
    val = 1;
    printf("val 1: %ld\t", val);
    big_val(a, val);
    val = 2;
    printf("val 2: %ld\t", val);
    big_val(b, val);
    printf("soma 1 + 2 = 3:");
    big_sum(c, a, b);
    exibe_bigint(c, val);

    // bigint -1 + (-1)
    val = -1;
    printf("val 1: %ld\t", val);
    printf("val 2: %ld\t", val);
    big_val(a, val);
    big_val(b, val);
    printf("soma -1 + (-1) = 0: ");
    big_sum(c, a, b);
    exibe_bigint(c, val);

    // bigint 256 + 256
    val = 256;
    printf("val 1: %ld\t", val);
    printf("val 2: %ld\t", val);
    big_val(a, val);
    big_val(b, val);
    printf("soma 256 + 256 = 512: ");
    big_sum(c, a, b);
    exibe_bigint(c, val);

    // teste big_sub
    printf("\nteste big_sub\n");
    // bigint 1 - 1
    val = 1;
    printf("val 1: %ld\t", val);
    printf("val 2: %ld\t", val);
    big_val(a, val);
    big_val(b, val);
    printf("subtração 1 - 1 = 0: ");
    big_sub(c, a, b);
    exibe_bigint(c, val);

    // bigint 1024 - 512
    val = 1024;
    printf("val 1: %ld\t", val);
    big_val(a, val);
    val = 512;
    printf("val 2: %ld\t", val);
    big_val(b, val);
    printf("subtração 1024 - 512 = 512: ");
    big_sub(c, a, b);
    exibe_bigint(c, val);

    // bigint 512 - 1024
    val = 512;
    printf("val 1: %ld\t", val);
    big_val(a, val);
    val = 1024;
    printf("val 2: %ld\t", val);
    big_val(b, val);
    printf("subtração 512 - 1024 = -512: ");
    big_sub(c, a, b);
    exibe_bigint(c, val);

    // teste big_mul
    printf("\nteste big_mul\n");
    // bigint 1 * 1
    val = 1;
    printf("val 1: %ld\t", val);
    big_val(a, val);
    val = 1;
    printf("val 2: %ld\t", val);
    big_val(b, val);
    printf("multiplicação 1 * 1 = 1: ");
    big_mul(c, a, b);
    exibe_bigint(c, val);

    // bigint 4 * 4
    val = 4;
    printf("val 1: %ld\t", val);
    printf("val 2: %ld\t", val);
    big_val(a, val);
    big_val(b, val);
    printf("multiplicação 4 * 4 = 16: ");
    big_mul(c, a, b);
    exibe_bigint(c, val);

    // bigint 1 * (-1)
    val = 1;
    printf("val 1: %ld\t", val);
    big_val(a, val);
    val = -1;
    printf("val 2: %ld\t", val);
    big_val(b, val);
    printf("multiplicação 1 * (-1) = -1: ");
    big_mul(c, a, b);
    exibe_bigint(c, val);

    // teste big_shl
    int n = 8;
    printf("\nteste big_shl\n");
    // bigint 1 << 8
    val = 1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("1 << 8 = 256:\t");
    big_val(a, val);
    big_shl(b, a, n);
    exibe_bigint(b, val);

    // bigint -1 << 8
    val = -1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("-1 << 8 = -256:\t");
    big_val(a, val);
    big_shl(b, a, n);
    exibe_bigint(b, val);

    // bigint 256 << 1
    val = 256;
    n = 1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("256 << 1 = 512:\t");
    big_val(a, val);
    big_shl(b, a, n);
    exibe_bigint(b, val);

    // teste big_shr
    printf("\nteste big_shr\n");
    // bigint 1 >> 1
    val = 1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("1 >> 1 = 0:\t");
    big_val(a, val);
    big_shr(b, a, n);
    exibe_bigint(b, val);

    // bigint -1 >> 1
    val = -1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("-1 >> 1 = 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF:\t");
    big_val(a, val);
    big_shr(b, a, n);
    exibe_bigint(b, val);

    // bigint 512 >> 1
    val = 512;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("512 >> 1 = 256:\t");
    big_val(a, val);
    big_shr(b, a, n);
    exibe_bigint(b, val);

    // teste big_sar
    printf("\nteste big_sar\n");
    // bigint 1 >> 1
    val = 1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("1 >> 1 = 0:\t");
    big_val(a, val);
    big_sar(b, a, n);
    exibe_bigint(b, val);

    // bigint -1 >> 1
    val = -1;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("-1 >> 1 = -1:\t");
    big_val(a, val);
    big_sar(b, a, n);
    exibe_bigint(b, val);

    // bigint 512 >> 1
    val = 512;
    printf("val 1: %ld\tn: %d\t", val, n);
    printf("512 >> 1 = 256:\t");
    big_val(a, val);
    big_sar(b, a, n);
    exibe_bigint(b, val);

    return 0;
}
