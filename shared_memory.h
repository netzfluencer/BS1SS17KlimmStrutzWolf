//
// Created by User on 24.05.2017.
//

#ifndef BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H
#define BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include "store_tools.h"

int sm_key = 4325;

int shm();

#endif //BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H
