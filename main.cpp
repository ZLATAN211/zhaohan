#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

using namespace std;

struct sem_inet{

    sem_t *pSet;
    int reader=1;
    pthread_mutex_t mutex_x=PTHREAD_MUTEX_INITIALIZER;

};

extern void read_lock(sem_inet *si);
//extern void write_lock(sem_inet *si);
extern void unlock(sem_inet *si);

int main() {

    pid_t  pid;
    pid=fork();
    sem_inet sem;
    //子进程
    if (pid==0){
        read_lock(&sem);
        cout<<"aaa"<<endl;
        unlock(&sem);
    } else{
        sleep(1);
        read_lock(&sem);
        cout<<"bbb"<<endl;
        unlock(&sem);
    }

    return 0;

}

//char *aa = "aaaa";
//char *bb = "bbbb";
//char *cc = (char *)malloc(sizeof(strlen(aa)+strlen(bb)));
//strcat(cc,aa);
//strcat(cc,bb);
//free(cc);

//    char *str="/home";
//    char *strs="/bin/";
//
//    while (1){
//        char *a="ls";
//        cout<<str<<endl;
////        cin>>a;
//        char *result=(char *)malloc(sizeof(strlen(a)+strlen(strs)));
//        strcat(result,strs);
//        strcat(result,a);
//        char *args[]={"bash",str,NULL};
//        pid_t pid;
//        pid=fork();
//        if (pid==0){
//            execve(result,args,NULL);
//        } else{
//            cout<<str;
//            sleep(3);
////            free(result);
//        }
//    }