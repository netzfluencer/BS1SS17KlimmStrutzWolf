#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"

//test

int main() {

    char *resp = "";


    put(8, "hgh", (char *) &resp);
    get(8, (char *) &resp);

    printf("%s\n", resp);



    put(8, "testing", (char *) &resp);
    get(8, (char *) &resp);

    printf("%s\n", resp);



    delete(8, (char *) &resp);

    printf("%s\n", resp);



    start();
    return 0;
}