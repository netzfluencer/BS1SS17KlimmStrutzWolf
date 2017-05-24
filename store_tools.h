#ifndef BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
#define BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H

#include <stdio.h>
#define STORELENGTH 10

struct key_value{
    int key;
    char *value;
};
struct key_value kv[STORELENGTH];

int put(int key, char *value, char *resp);
int get(int key, char *resp);
int delete(int key, char *resp);

#endif //BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
