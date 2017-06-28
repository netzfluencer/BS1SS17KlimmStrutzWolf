//
// Created by alex on 28.06.17.
//
#include <stdio.h>
#include "persistent.h"
#include "socket.h"

FILE *file;
file = fopen("data.txt", "w+");


void auslesen(char key[], char resp[]){
    while(fscanf(file, "%s %s", *key, *resp)){
        
    }

}

void schreiben(){

}
