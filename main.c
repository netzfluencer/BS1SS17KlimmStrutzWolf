#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"

int main() {

    char *resp = "";
    //char resp[BUFSIZ];




    put(8, "hgh", (char *) &resp);
    get(8, (char *) &resp);

    printf("%s\n", resp);



    put(8, "testing", (char *) &resp);
    printf("Alt: %s\n", resp);
    get(8, (char *) &resp);


    printf("%s\n", resp);



    //Socket anlegen
    start();

    return 0;
}