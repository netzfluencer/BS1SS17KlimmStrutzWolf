#include "store_tools.h"

// Fragen:
// 1. Wir koennten in Anbetracht von REST hier mit HTTP Status Codes arbeiten - EDIT: Besser nicht
// 2. Wir sollten die Key vllt als char deklarieren
// 3. Die Übergabe des structs macht im Moment keinen Sinn, da das struct Global ist


int put(int key, char *value, char *resp, struct key_value kv[]){
    int emptyIndex = -1;
    *resp = (char) "";
    for(int i = 0; i < sizeof(kv); i++){
        // Falls der Key existiert: Ueberschreiben, alten Wert zurueckgeben und return true
        if(kv[i].key == key){
            *resp = (char) kv[i].value;
            kv[i].value = value;
            return 1;
        }
        // Einen leeren Index aufheben, falls der Key nicht existiert
        if(kv[i].key == NULL){
            emptyIndex = i;
        }
    }

    // Wenn es einen leeren Index gab, dort rein speichern.
    if(emptyIndex > -1) {
        kv[emptyIndex].key = key;
        *resp = (char) "";
        kv[emptyIndex].value = value;
        return 1;
    }

    *resp = (char) "Error: Put was not not successful.";
    return 0;
}

int get(int key, char *resp, struct key_value kv[]) {
    *resp = (char) "";
    for (int i = 0; i < sizeof(kv); i++) {
        if (kv[i].key == key) {
            *resp = (char) kv[i].value;
            return 1;
        }
    }

    *resp = (char) "Error: Key not found.";
    return 0;
}

int delete(int key, char *resp, struct key_value kv[]) {
    *resp = (char) "";
    for (int i = 0; i < sizeof(kv); i++){
        if (kv[i].key == key){
            *resp = (char) kv[i].value;
            kv[i].value = NULL;
            kv[i].key = NULL;
            return 1;
        }
    }

    *resp = (char) "Error: Key not found.";
    return 0;
}


