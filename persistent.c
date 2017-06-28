//
// Created by alex on 28.06.17.
//
#include <stdio.h>
#include "persistent.h"
#include "socket.h"

FILE *dataFile;




void auslesen(char key[], char resp[]){
    //opens file in mode r for read
    dataFile = fopen("data.txt", "r");
    while(fscanf(dataFile, "%s %s", key, resp) > 0){
        //output data in a useful way
        strcat(resp, );
        fclose(dataFile);
    }

}

void schreiben(char key[], char resp[]){
    dataFile = fopen("data.txt", "w");
    fprintf(dataFile, "%s %s\n", key, resp);
}
