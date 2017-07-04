//
// Created by alex on 28.06.17.
//
#include <stdio.h>
#include "persistent.h"
#include "socket.h"

FILE *dataFile;
int c;

void auslesen(char resp[]) {
    //opens file in mode r for read

    dataFile = fopen("keyvalue.txt", "r");
    if (dataFile != NULL) {
        printf("Database found.\n");
        int ivall = 0;
        while ((c = fgetc(dataFile)) != EOF) {
            char tmp = c;
            resp[ivall] = tmp;
            ivall++;
        }
        resp[ivall - 1] = NULL;
        fclose(dataFile);
    } else {
        printf("Database not found, creating new one\n");
        dataFile = fopen("keyvalue.txt", "w");
        fclose(dataFile);
    }

}

void schreiben() {
    dataFile = fopen("keyvalue.txt", "w+");
    char *tempresp = " ";
    for(int i = 0; i <= STORELENGTH; i++){
        if(strcmp(kv[i].key, NULL) != 0){
            fprintf(dataFile, "%s\n%s\n", kv[i].key, kv[i].value);
        }
        else{
        }
    }
    fclose(dataFile);
    exit(1);
}

