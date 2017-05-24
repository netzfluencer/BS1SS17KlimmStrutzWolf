#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"
#include "shared_memory.h"


int main() {

    shm();

    char *resp = "";


    put(8, "hgh", (char *) &resp, kv);
    get(8, (char *) &resp, kv);

    printf("%s\n", resp);



    put(8, "testing", (char *) &resp, kv);
    get(8, (char *) &resp, kv);

    printf("%s\n", resp);



    delete(8, (char *) &resp, kv);

    printf("%s\n", resp);



    start();
    return 0;
}