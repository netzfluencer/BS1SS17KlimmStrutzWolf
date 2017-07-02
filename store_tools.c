#include <string.h>
#include <stdbool.h>
#include "store_tools.h"

int get(char key[], char resp[]) {
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        if (strcmp(kv[i].key, key) == 0) {
            strcpy(resp, "Der gesuchte Value ist '");
            strcat(resp, kv[i].value);
            strcat(resp, "'.\n");
            return 1;
        }
    }
    strcpy(resp, "Error on get: Key not found.\n");
    return -1;
}


int put(char key[], char value[], char resp[]) {
    int emptyIndex = -1;
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        // Falls der Key existiert: Ueberschreiben, alten Wert zurueckgeben und return true
        if (strcmp(kv[i].key, key) == 0) {
            //Clientausgabe
            strcpy(resp, "Beim Key '");
            strcat(resp, kv[i].key);
            strcat(resp, "' wird der Value '");
            strcat(resp, kv[i].value);
            strcat(resp, "' mit dem Value '");
            strcat(resp, value);
            strcat(resp, "' überschrieben.\n");


            strcpy(kv[i].value, value);
            return 1;
        }
        // Einen leeren Index aufheben, falls der Key nicht existiert
        emptyIndex = i;
    }

    // Wenn es einen leeren Index gab, dort rein speichern.
    if (emptyIndex > -1) {
        strcpy(kv[emptyIndex].key, key);
        strcpy(kv[emptyIndex].value, value);

        //Clientausgabe
        strcpy(resp, "Der Key '");
        strcat(resp, key);
        strcat(resp, "' mit dem Value '");
        strcat(resp, value);
        strcat(resp, "' wird eingefügt.\n");
        return 1;
    }
    strcpy(resp, "Error on put: Action not successfull\n");
    return -1;
}


int delete(char key[], char resp[]) {
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        if (strcmp(kv[i].key, key) == 0) {
            //Clientausgabe
            strcpy(resp, "Der Key '");
            strcat(resp, kv[i].key);
            strcat(resp, "' mit dem Value '");
            strcat(resp, kv[i].value);
            strcat(resp, "' wird gelöscht.\n");

            strcpy(kv[i].value, "");
            strcpy(kv[i].key, "");
            return 0;
        }
    }

    strcpy(resp, "Error on delete: Key not found.\n");
    return -1;
}


int fillStore(char resp[]) {
    int respIT = 0;
    while (true) {
        if(resp[respIT] == NULL){
            break;
        }
            while (resp[respIT] != NULL && resp[respIT] != 32) {
                printf("\nKey: %c", resp[respIT]);
                //strcpy(kv[respIT].key, resp[respIT]);
                respIT++;
        }
            respIT++;
            while (resp[respIT] != 32 && resp[respIT] != NULL) {
                printf("\nValue: %c", resp[respIT]);
                //strcpy(kv[respIT].value, ""+resp[respIT]);
                respIT++;
            }
            respIT++;

    }
}

