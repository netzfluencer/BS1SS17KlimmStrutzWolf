#ifndef BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
#define BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H

#include <stdio.h>

struct key_value{
    int key;
    char *value;
};
struct key_value kv[10];

int put(int key, char *value, char *resp, struct key_value kv[]);
int get(int key, char *resp, struct key_value kv[]);
int delete(int key, char *resp, struct key_value kv[]);

#endif //BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
