//
// Created by User on 24.05.2017.
//

#include "shmem.h"

int shmem() {
    char *resp = "";
    struct key_value *myPtr;
    int sm_key = 4325;

    int shID = shmget(sm_key, STORELENGTH * sizeof(struct key_value), IPC_CREAT | 0777);

    if(shID >= 0) {
        myPtr = (struct key_value *) shmat(shID, 0, 0);
        put(5, "testeer", &resp);
        for(int i= 0; i < STORELENGTH; i++) {
            myPtr[i] = kv[i];
            printf("%s\n", myPtr[i].value);
        }

    }
    else {
        perror("shmget");
    }

    return 0;
}

