//
// Created by User on 11.05.2017.
//

#include "store_tools.h"


int put(int key, char *value, struct key_value kv[]){
     for(int i = 0; i < sizeof(kv); i++){
        if(kv[i].key == key){
            int tmp = kv[i].key;
            kv[i].key = key;
            kv[i].value = value;
            return tmp;
        }
     }
        for(int j = 0; j < sizeof(kv); j++){
            if(kv[j].key == NULL){
                kv[j].key = key;
                kv[j].value = value;
                return 0;
            }
        }
        return -1;
    }

char* get(int key, struct key_value kv[]) {
    for (int i = 0; i < sizeof(kv); i++) {
        if (kv[i].key == key) return kv[i].value ;
    }
    return (char*)stderr;
}

char* delete(int key, struct key_value kv[]) {
    for (int i = 0; i < sizeof(kv); i++){
        if (kv[i].key == key){
            char* tmp = kv[i].value;
            kv[i].value = NULL;
            return tmp;
        }
    }
    return (char*)stderr;
}


