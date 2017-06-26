#include "shmem.h"
#include "string.h"

int shmem() {
    int shID = shmget(IPC_PRIVATE, STORELENGTH * sizeof(KEY_VALUE), IPC_CREAT | 0777);

    if (shID >= 0) {
        kv = (struct key_value *) shmat(shID, 0, 0);
        for (int i = 0; i < STORELENGTH; i++) {
            kv[i] = kv_init[i];
        }

    } else {
        perror("shmget");
    }

    int rcshID = shmget(IPC_PRIVATE, sizeof(rc), IPC_CREAT | 0777);

    if (rcshID >= 0) {
        rc = (int *) shmat(rcshID, 0, 0);
    } else {
        perror("shmget");
    }
    return 0;
}

