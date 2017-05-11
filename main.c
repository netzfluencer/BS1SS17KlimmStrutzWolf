#include <stdio.h>

struct key_value{
    int key;
    char* value;
};

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
    return stderr;
}

int delete(char *key) {

}

int main() {
    struct key_value kv[10];
    //put(8, 'dasd', kv);
    return 0;

}