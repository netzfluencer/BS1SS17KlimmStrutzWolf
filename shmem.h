//
// Created by User on 24.05.2017.
//

#ifndef BS1SS17KLIMMSTRUTZWOLF_SHMEM_H
#define BS1SS17KLIMMSTRUTZWOLF_SHMEM_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include "store_tools.h"
#include <sys/sem.h>

struct key_value *kv;

int shmem();

#endif //BS1SS17KLIMMSTRUTZWOLF_SHMEM_H

