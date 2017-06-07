#ifndef BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
#define BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H

#include <stdio.h>
#include "shmem.h"
#define STORELENGTH 10

typedef struct key_value{
    char key[BUFSIZ];
    char value[BUFSIZ];
} KEY_VALUE;
struct key_value kv_init[STORELENGTH];


int put(char key[], char value[], char resp[]);
int get(char key[], char resp[]);
int delete(char key[], char resp[]);
int strtrenn(char *str, char *token[]);


#endif //BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
