  /* Davi_Rangel 2411930 3WB */
  /* Victor_Hugo_Brito 2421278 3WB */

#include <string.h>
#include "bigint.h"

void big_val (BigInt res, long val){
    long temp = val;
    for (int i = 0; i < 8; i++){ // copia os 8 bytes de val pra res
        res[i] = temp & 0xFF; // copia o byte atual pra res
        temp = temp >> 8; // remove o byte ja copiado
    }
    unsigned char extensao = 0;
    if ((res[7] & 0x80)>>7 == 1) extensao = 0xFF; // se o bit mais significante for 1 a extensao de sinal sera 1
    for (int i = 8; i < 16; i++){
        res[i] = extensao; // extensao de sinal
    }
}

void big_comp2(BigInt res, BigInt a){
    for (int i = 0; i < 16; i++){ // percorre todo o vetor
        res[i] = ~(a[i]); // inverte todos os bits do byte atual
    }
    int soma, resto = 1;
    for (int i = 0; i < 16 && resto > 0; i++){
        soma = res[i] + resto;
        res[i] = soma & 0xFF;
        resto = soma >> 8;
    }
}

void big_sum(BigInt res, BigInt a, BigInt b){
    int soma; // tipo maior pra guardar o valor completo da soma
    unsigned char resto = 0; // resto começa em 0 pra primeira soma
    for (int i = 0; i < 16; i++){
        soma = a[i] + b[i] + resto; // soma dos bytes + o resto da soma anterior
        res[i] = (soma & 0xFF); // somente o byte menos significativo
        if (soma > 0xFF) resto = 1; // se o valor de soma for maior do que um char consegue guardar, o resto é 1 (vai um)
        else resto = 0;
    }
}

void big_sub(BigInt res, BigInt a, BigInt b){
    BigInt c;
    big_comp2(c, b); // -b
    big_sum(res, a, c); // a + (-b)
}

void big_mul(BigInt res, BigInt a, BigInt b){
    for (int i = 0; i < 16; i++) {
        res[i] = 0; // res = 0
    }
    for (int i = 0; i < 16; i++){
        unsigned int resto = 0;
        for (int j = 0; j < 16; j++){
            if (i + j < 16){ // limite do vetor
                unsigned int produto = (unsigned int)a[j] * b[i] + res[i + j] + resto; // o produto de cada unidade dos vetores multiplicada
                res[i + j] = produto & 0xFF;
                resto = produto >> 8;
            }
        }
    }
}

void big_shl(BigInt res, BigInt a, int n){
    memcpy(res, a, 16);
    for (int i = 0; i < n; i++){ // loop com o n
        unsigned char temp = 0, temp2 = 0;
        for (int j = 0; j < 16; j++){ // percorre o vetor
            temp2 = (res[j] & 0x80) >> 7; // prepara a extensao de sinal
            res[j] = (res[j] << 1) | temp; // copia o valor anterior
            temp = temp2; // salva o valor atual para o proximo loop
        }
    }
}

void big_shr(BigInt res, BigInt a, int n){
    memcpy(res, a, 16);
    for (int i = 0; i < n; i++){
        unsigned char temp = 0, temp2 = 0;
        for (int j = 15; j >= 0; j--){ // percorre o vetor ao contrario
            temp2 = res[j] & 0x01; // bit menos significativo
            res[j] = (res[j] >> 1) | (temp << 7); // copia o valor anterior
            temp = temp2; // salva o valor atual para o proximo loop
        }
    }
}

void big_sar(BigInt res, BigInt a, int n){
    memcpy(res, a, 16);
    for (int i = 0; i < n; i++){
        unsigned char temp = 0, temp2 = 0;
        if (res[15] & 0x80) temp = 0x80; // extensao de sinal
        for (int j = 15; j >= 0; j--){
            temp2 = res[j] & 0x01;
            res[j] = (res[j] >> 1) | temp;
            temp = temp2 << 7;
        }
    }
}