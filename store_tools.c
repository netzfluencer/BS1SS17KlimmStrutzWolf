#include <string.h>
#include "store_tools.h"

// Fragen ans Team:
// 1. Wir koennten in Anbetracht von REST hier mit HTTP Status Codes arbeiten - EDIT: Besser nicht
// 2. Wir sollten die Key vllt als char deklarieren
// 3. Die Übergabe des structs macht im Moment keinen Sinn, da das struct Global ist
// 4. Eine Init-Funktion

// Fragen an Betreuer:
// 1. Socket Server testing: Wie geht das einfach & schnell?
// 2. Aufgaben Punktesystem: bei bestehen 50 Punkte oder ist das maximal Punktzahl für die beste Lösung?


int get(int key, char *resp) {
    *resp = (char) "";
    for (int i = 0; i < sizeof(kv)/ sizeof(struct key_value); i++) {
        if (kv[i].key == key) {
            *resp = (char) kv[i].value;
            return 1;
        }
    }

    *resp = (char) "Error: Key not found.";
    return -1;
}


int put(int key, char *value, char *resp){
    int emptyIndex = -1;
    *resp = (char) "";
    for(int i = 0; i < sizeof(kv)/ sizeof(struct key_value); i++){
        // Falls der Key existiert: Ueberschreiben, alten Wert zurueckgeben und return true
        if(kv[i].key == key) {
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
    return -1;
}


int delete(int key, char *resp) {
    *resp = (char) "";
    for (int i = 0; i < sizeof(kv)/ sizeof(struct key_value); i++){
        if (kv[i].key == key){
            *resp = (char) kv[i].value;
            kv[i].value = NULL;
            kv[i].key = NULL;
            return 1;
        }
    }

    *resp = (char) "Error: Key not found.";
    return -1;
}

int strtrenn(char *in, char *in_splitted[]){
    int i=0;
    in_splitted[0]= strtok(in, " ");
    while(in_splitted[i++] && i<3)
        in_splitted[i] = strtok(NULL, " ");
    return i;
}


