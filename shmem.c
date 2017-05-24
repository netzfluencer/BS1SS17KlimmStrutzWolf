//
// Created by User on 24.05.2017.
//

#include "shmem.h"

int shmem() {
    struct key_value *myPtr;


    int shID = shmget(sm_key, kvlength * sizeof(struct key_value), IPC_CREAT | 0777);

    if(shID >= 0) {
        myPtr = (struct key_value *) shmat(shID, 0, 0);
            for(int i= 0; i < STORELENGTH; i++) {
                myPtr[i] = kv[i];
            }
        
    }
    else {
        perror("shmget");
    }

    return 0;
}

