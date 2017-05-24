//
// Created by User on 24.05.2017.
//

#ifndef BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H
#define BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

const int sm_key = 4325;


void *shmat(int shmid, const void *shmaddr, int shmflg);
int shmdt(const void *shmaddr);
int shmctl(int shmid, int kommando, struct shmid_ds *buf);

#endif //BS1SS17KLIMMSTRUTZWOLF_SHARED_MEMORY_H
