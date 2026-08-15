/* Davi_Rangel 2411930 3WB */
/* Victor_Hugo_Brito 2421278 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera_codigo.h"

/* escreve inteiro em code[] */
static void escreve_int(unsigned char code[], int *pos, int valor) {
    code[*pos] = valor & 0xFF;
    code[*pos + 1] = (valor >> 8) & 0xFF;
    code[*pos + 2] = (valor >> 16) & 0xFF;
    code[*pos + 3] = (valor >> 24) & 0xFF;
    *pos += 4;
}

/* escreve byte em code[] */
static void escreve_byte(unsigned char code[], int *pos, unsigned char val) {
    code[*pos] = val;
    (*pos)++;
}

static char obter_offset(char *var) {
    if (var[0] == 'p') {
        return -24; /* p0 em -24(%rbp) */
    }
    else if (var[0] == 'v') {
        int idx = atoi(var + 1);
        return -20 + (idx * 4); /* v0=-20, v1=-16, v2=-12, v3=-8, v4=-4 */
    }
    return 0;
}

/* reg: 0 = %eax, 1 = %ecx */
static void carregar_em_reg(unsigned char code[], int *pos, char *varpc, unsigned char reg) {
    if (varpc[0] == '$') {
        int val = atoi(varpc + 1);
        if (reg == 0) {
            escreve_byte(code, pos, 0xb8);
        } else {
            escreve_byte(code, pos, 0xb9);
        }
        escreve_int(code, pos, val);
    } else {
        char offset = obter_offset(varpc);
        escreve_byte(code, pos, 0x8b);
        escreve_byte(code, pos, reg == 0 ? 0x45 : 0x4d);
        escreve_byte(code, pos, offset);
    }
}

void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int pos = 0;
    int enderecos_funcoes[50]; /* Guarda início de cada função LBS */
    int func_id = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (linha[0] == '\n' || linha[0] == '\0') continue;

        char comando[20];
        if (sscanf(linha, "%s", comando) != 1) continue;

        /* function */
        if (strcmp(comando, "function") == 0) {
            enderecos_funcoes[func_id] = pos;
            *entry = (funcp)((void*)(code + pos));
            func_id++;

            escreve_byte(code, &pos, 0x55); /* push %rbp */
            escreve_byte(code, &pos, 0x48); /* mov %rsp, %rbp */
            escreve_byte(code, &pos, 0x89);
            escreve_byte(code, &pos, 0xe5);
            
            escreve_byte(code, &pos, 0x48); /* sub $32, %rsp */
            escreve_byte(code, &pos, 0x83);
            escreve_byte(code, &pos, 0xec);
            escreve_byte(code, &pos, 0x20);

            escreve_byte(code, &pos, 0x89); /* mov %edi, -24(%rbp) - salva p0 */
            escreve_byte(code, &pos, 0x7d);
            escreve_byte(code, &pos, 0xe8);
        }

        /* end */
        else if (strcmp(comando, "end") == 0) {
            continue;
        }

        /* ret */
        else if (strcmp(comando, "ret") == 0) {
            char varpc[10];
            sscanf(linha, "ret %s", varpc);

            /* Valor de retorno no %eax */
            if (varpc[0] == '$') {
                int val = atoi(varpc + 1);
                escreve_byte(code, &pos, 0xb8);
                escreve_int(code, &pos, val);
            } else {
                char offset = obter_offset(varpc);
                escreve_byte(code, &pos, 0x8b);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset);
            }

            escreve_byte(code, &pos, 0xc9);
            escreve_byte(code, &pos, 0xc3);
        }

        /* zret */
        else if (strcmp(comando, "zret") == 0) {
            char varpc1[10], varpc2[10];
            sscanf(linha, "zret %s %s", varpc1, varpc2);

            carregar_em_reg(code, &pos, varpc1, 0);

            escreve_byte(code, &pos, 0x83); /* cmpl $0, %eax */
            escreve_byte(code, &pos, 0xf8);
            escreve_byte(code, &pos, 0x00);

            int jump_offset = (varpc2[0] == '$') ? 0x07 : 0x05;
            escreve_byte(code, &pos, 0x75); /* jne (pula o retorno) */
            escreve_byte(code, &pos, jump_offset);

            /* Valor de retorno no %eax */
            if (varpc2[0] == '$') {
                int val = atoi(varpc2 + 1);
                escreve_byte(code, &pos, 0xb8);
                escreve_int(code, &pos, val);
            } else {
                char offset = obter_offset(varpc2);
                escreve_byte(code, &pos, 0x8b);
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset);
            }

            escreve_byte(code, &pos, 0xc9);
            escreve_byte(code, &pos, 0xc3);
        }

        else if (linha[0] == 'v') {
            int idx_dest;
            char op1[10], op[5], op2[10];
            
            /* call */
            if (sscanf(linha, "v%d = call %s %s", &idx_dest, op1, op2) == 3) {
                int num_func = atoi(op1);
                char offset_dest = -20 + (idx_dest * 4);

                carregar_em_reg(code, &pos, op2, 0); /* argumento em %eax */

                escreve_byte(code, &pos, 0x89); /* movl %eax, %edi */
                escreve_byte(code, &pos, 0xc7);

                int pos_call = pos;
                escreve_byte(code, &pos, 0xe8);
                
                /* calculo offset relativo */
                int offset_call = enderecos_funcoes[num_func] - (pos_call + 5);
                escreve_int(code, &pos, offset_call);

                /* salva retorno no RA */
                escreve_byte(code, &pos, 0x89); /* movl %eax, offset(%rbp) */
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset_dest);
            }

            /* soma */
            else if (sscanf(linha, "v%d = %s %s %s", &idx_dest, op1, op, op2) == 4) {
                char offset_dest = -20 + (idx_dest * 4);

                carregar_em_reg(code, &pos, op1, 0); /* op1 -> %eax */
                carregar_em_reg(code, &pos, op2, 1); /* op2 -> %ecx */

                if (strcmp(op, "+") == 0) {
                    escreve_byte(code, &pos, 0x01); /* addl %ecx, %eax */
                    escreve_byte(code, &pos, 0xc8);
                } else if (strcmp(op, "-") == 0) {
                    escreve_byte(code, &pos, 0x29); /* subl %ecx, %eax */
                    escreve_byte(code, &pos, 0xc8);
                } else if (strcmp(op, "*") == 0) {
                    escreve_byte(code, &pos, 0x0f); /* imull %ecx, %eax */
                    escreve_byte(code, &pos, 0xaf);
                    escreve_byte(code, &pos, 0xc1);
                }

                /* salva resultado no RA */
                escreve_byte(code, &pos, 0x89); /* movl %eax, offset(%rbp) */
                escreve_byte(code, &pos, 0x45);
                escreve_byte(code, &pos, offset_dest);
            }
            
            /* atribuição */
            else if (sscanf(linha, "v%d = %s", &idx_dest, op1) == 2) {
                char offset_dest = -20 + (idx_dest * 4);

                /* constante */
                if (op1[0] == '$') {
                    int val = atoi(op1 + 1);
                    escreve_byte(code, &pos, 0xc7);
                    escreve_byte(code, &pos, 0x45);
                    escreve_byte(code, &pos, offset_dest);
                    escreve_int(code, &pos, val);
                } else {
                    char offset_orig = obter_offset(op1);
                    escreve_byte(code, &pos, 0x8b);
                    escreve_byte(code, &pos, 0x4d);
                    escreve_byte(code, &pos, offset_orig);

                    escreve_byte(code, &pos, 0x89);
                    escreve_byte(code, &pos, 0x4d);
                    escreve_byte(code, &pos, offset_dest);
                }
            }
        }
    }
}
