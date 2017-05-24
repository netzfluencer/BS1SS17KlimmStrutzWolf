#include "shared_memory.h"

int shm() {
    struct key_value *myPtr;
    int kvlength = 10;

    // bestimmen der Store Groesse
    struct key_value kv[kvlength];

    int shID = shmget(sm_key, kvlength * sizeof(struct key_value), IPC_CREAT | 0777);

    if(shID >= 0) {
        myPtr = (struct key_value *) shmat(shID, 0, 0);
        if(myPtr == (struct key_value *) -1) {
            perror("shmat");
        }
        else {
            for(int i= 0; i < kvlength; i++) {
                myPtr[i] = kv[i];
            }
        }
    }
    else {
        perror("shmget");
    }

    return 0;
}
