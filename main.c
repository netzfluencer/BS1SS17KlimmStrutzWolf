#include <stdio.h>
#include <stdlib.h>

#include "store_tools.h"
#include "socket.h"


int main() {
    put(8, "hgh", kv);
    get(8, kv);
    delete(8, kv);
    start();
    return 0;

}