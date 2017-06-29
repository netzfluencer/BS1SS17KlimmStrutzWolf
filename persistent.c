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
    if(fopen("keyvalue.txt", "r") != NULL) {
        printf("Database found.\n");
        dataFile = fopen("keyvalue.txt", "r");
        while (c == getc(dataFile) != EOF) {
            //output data in a useful way
            strcat(resp, c);
            fclose(dataFile);
        }
    }
    else{
        printf("Database not found, creating new one\n");
        dataFile = fopen("keyvalue.txt", "w");
        fclose(dataFile);
    }

}

void schreiben(char key[], char resp[]) {
    dataFile = fopen("keyvalue.txt", "w");
    fprintf(dataFile, "%s %s\n", key, resp);
}
