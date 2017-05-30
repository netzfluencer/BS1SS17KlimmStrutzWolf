#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"

int main() {
    //kv_init[9].key = 123;
    //kv_init[9].value = "hi";
    shmem();
    //printf("Ausgabe: %s\n",kv[9].value);
    //kv[9].value = "123";
    //printf("Ausgabe: %s\n",kv[9].value);

    char *resp = "";
    //char resp[BUFSIZ];


    put(4, "depp", (char *) &resp);
    printf("PUT return: %s\n", resp);

    get(4, (char *) &resp);
    printf("GET return: %s\n", resp);

    put(4, "lol", (char *) &resp);
    printf("PUT return: %s\n", resp);






    //Socket anlegen
    start();

    return 0;
}