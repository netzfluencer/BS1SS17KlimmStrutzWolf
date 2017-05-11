//
// Created by User on 11.05.2017.
//

#include <stdio.h>
#include "store_tools.h"

int put(int key, char *value, struct key_value kv[]) {
    for (int i = 0; i < sizeof(kv); i++) {
        if (kv[i].key == key) {
            if (kv[i].key == NULL) {
                kv[i].key = key;
                kv[i].value = value;
            }
            else {
                int tmp = kv[i].key;
                kv[i].key = key;
                kv[i].value = value;
                return tmp;
            }
        }
    }
    return 0;
}

char* get(int key, struct key_value kv[]) {
    for (int i = 0; i < sizeof(kv); i++) {
        if (kv[i].key == key) return kv[i].value ;
    }
    return (char*)stderr;
}

int delete(char *key, struct key_value kv[]) {

}


