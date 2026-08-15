#ifndef GERA_CODIGO_H
#define GERA_CODIGO_H

#include <stdio.h>

typedef int (*funcp) (int x);
void gera_codigo (FILE *f, unsigned char code[], funcp *entry);

#endif