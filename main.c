#include <stdio.h>

int main() {
    char *storeValue[10];
    char *storeKey[10];
    for (int i = 0; i < 10; i++){
        //storeKey[i] = 'KEY'+i;
        //storeValue[i] = 'VALUE'+i;
        printf("\n Der Key ist %s", storeKey[i]);
        printf("\n Der Value ist %s", storeValue[i]);
    }
}

int put(char *key, char *value, char *storeValue[], char *storeKey[]) {
    for (int i = 0; i < sizeof(storeValue); i++) {
        if (storeKey[i] == key) {
            if (storeKey[i] == NULL) {
                storeKey[i] = key;
            }
            else {
                int tmp = *storeKey[i];
                storeKey[i] = key;
                return tmp;
            }
        }
    }
}

int get(char *key, char *storeValue[], char *storeKey[]) {
    for (int i = 0; i < sizeof(storeValue); i++) {
        if (storeKey[i] == key) return 0;
    }
    return -1;
}

int delete(char *key) {

}