#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"

int main() {
    shmem();


    char *resp = "";
    //char resp[BUFSIZ];


    /* TESTDATEN
    put(4, "depp", (char *) &resp);
    printf("PUT return: %s\n", resp);

    get(4, (char *) &resp);
    printf("GET return: %s\n", resp);

    put(4, "lol", (char *) &resp);
    printf("PUT return: %s\n", resp);
    */
    //Socket anlegen
    start();

    return 0;
}