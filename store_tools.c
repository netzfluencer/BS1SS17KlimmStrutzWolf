#include <string.h>
#include "store_tools.h"

int get(char key[], char resp[]) {
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        if (strcmp(kv[i].key, key) == 0 ) {
            strcpy(resp, kv[i].value);
            return 1;
        }
    }
    strcpy(resp, "Error: Get was not successfull.");
    return -1;
}


int put(char key[], char value[], char resp[]){
    int emptyIndex = -1;
    strcpy(resp, "");
    for(int i = 0; i < STORELENGTH; i++){
        // Falls der Key existiert: Ueberschreiben, alten Wert zurueckgeben und return true
        if(strcmp(kv[i].key, key) == 0) {
            strcpy(resp, kv[i].value);
            strcpy(kv[i].value, value);
            return 1;
        }
        // Einen leeren Index aufheben, falls der Key nicht existiert
            emptyIndex = i;
    }

    // Wenn es einen leeren Index gab, dort rein speichern.
    if(emptyIndex > -1) {
        strcpy(kv[emptyIndex].key, key);
        strcpy(resp, "");
        strcpy(kv[emptyIndex].value, value);
        return 1;
    }
    strcpy(resp, "Error: Put was not successful.");
    return -1;
}


int delete(char key[], char resp[]){
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++){
        if (strcmp(kv[i].key, key) == 0){
            strcpy(resp, kv[i].value);
            strcpy(kv[i].value, "");
            strcpy(kv[i].key, "");
            return 0;
        }
    }

    strcpy(resp, "Error: Key not found.");
    return -1;
}




