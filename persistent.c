//
// Created by alex on 28.06.17.
//
#include <stdio.h>
#include "persistent.h"
#include "socket.h"

FILE *dataFile;
int c;

int sucheLog() {
    if ((dataFile = fopen("keyvalue.txt", "r")) == NULL) {
        return -1;
    }
    else {
        return 0;
    }
}

void auslesen(char resp[]) {
    //opens file in mode r for read
    dataFile = fopen("keyvalue.txt", "r");
    while (c == getc(dataFile) != EOF) {
        //output data in a useful way
        strcat(resp, c);
        fclose(dataFile);
    }

}

void schreiben(char key[], char resp[]) {
    dataFile = fopen("data.txt", "w");
    fprintf(dataFile, "%s %s\n", key, resp);
}

void neuErstellen() {

}
