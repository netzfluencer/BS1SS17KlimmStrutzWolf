//
// Created by alex on 28.06.17.
//
#include <stdio.h>
#include "persistent.h"
#include "socket.h"

FILE *dataFile;
int c;
char temp[BUFSIZ];

void auslesen(char resp[]) {
    //opens file in mode r for read

    dataFile = fopen("keyvalue.txt", "r");
    if(dataFile != NULL) {
        printf("Database found.\n");
        while ((c = fgetc(dataFile)) != EOF) {
            printf("%d\n", c);
            strcat(temp, ""+c);
            printf("%s\n", temp);
        }
        fclose(dataFile);
    }
    else{
        printf("Database not found, creating new one\n");
        fclose(dataFile);
        dataFile = fopen("keyvalue.txt", "w");
        fclose(dataFile);
    }

}

void schreiben(char key[], char resp[]) {
    dataFile = fopen("keyvalue.txt", "w");
    fprintf(dataFile, "%s %s\n", key, resp);
}
