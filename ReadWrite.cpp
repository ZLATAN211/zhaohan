//
// Created by zhaohan on 2021/7/20.
//

#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <bits/semaphore.h>

using namespace std;

#define SEM_NAMES "/sem_names"

struct sem_inet{

    sem_t *pSet;
    int reader=1;
    pthread_mutex_t mutex_x=PTHREAD_MUTEX_INITIALIZER;

};

sem_inet *si;
void read_lock(sem_inet *si){

    if (si->reader==0){

        pthread_mutex_lock(&si->mutex_x);
        sem_wait(si->pSet);
        pthread_mutex_unlock(&si->mutex_x);

    } else if (si->pSet== nullptr){

        pthread_mutex_lock(&si->mutex_x);
        si->pSet=sem_open(SEM_NAMES, O_CREAT, 0666, 1);
        sem_wait(si->pSet);
        pthread_mutex_unlock(&si->mutex_x);

    }

}

void write_lock(sem_inet *si){

    if (si->reader==1){

        if (si->pSet!= nullptr){

            pthread_mutex_lock(&si->mutex_x);
            sem_wait(si->pSet);
            pthread_mutex_unlock(&si->mutex_x);

        } else{

            pthread_mutex_lock(&si->mutex_x);
            si->pSet = sem_open(SEM_NAMES, O_CREAT, 0666, 1);
            sem_wait(si->pSet);
            si->reader == 0;
            pthread_mutex_unlock(&si->mutex_x);

        }
    } else {

        pthread_mutex_lock(&si->mutex_x);
        sem_wait(si->pSet);
        pthread_mutex_unlock(&si->mutex_x);

    }

}

void unlock(sem_inet *si){

    si->pSet== nullptr;
    si->reader==1;

}
