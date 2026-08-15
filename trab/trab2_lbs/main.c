#include <stdio.h>
#include <stdlib.h>
#include "gera_codigo.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("uso: %s <arquivo.lbs> <parametro>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("erro ao abrir %s\n", argv[1]);
        return 1;
    }

    funcp funcLBS = NULL;
    unsigned char code[1024];

    gera_codigo(fp, code, &funcLBS);
    fclose(fp);

    if (!funcLBS) {
        printf("erro na geracao\n");
        return 1;
    }
    
    int res = (*funcLBS)(atoi(argv[2]));
    printf("resultado: %d\n", res);

    return 0;
}