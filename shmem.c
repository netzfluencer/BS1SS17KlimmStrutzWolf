#include "shmem.h"
#include "string.h"

int shmem() {
    int sm_key = 4325;

    int shID = shmget(IPC_PRIVATE, STORELENGTH* sizeof(KEY_VALUE), IPC_CREAT | 0777);

    if(shID >= 0) {
        kv = (struct key_value *) shmat(shID, 0, 0);
        for(int i= 0; i < STORELENGTH; i++) {
            kv[i] = kv_init[i];
            //printf("%s\n", kv[i].value);
        }

    }
    else {
        perror("shmget");
    }

    return 0;
}

