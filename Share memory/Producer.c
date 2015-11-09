#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "data.h"

int main(){
    int running = 1;
    void * shared_memory = (void *)0;
    struct share_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;

    // get shared memory with the key
    shmid = shmget((key_t)1234 , sizeof(struct share_use_st) , 0666 | IPC_CREAT);

    if(shmid == -1){
        fprintf(stderr, "shmr get failed \n" );
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid , (void * )0  , 0);

    if (shared_memory == (void *) -1 ) {
        fprintf(stderr, "shmat failed \n");
        exit(EXIT_FAILURE);
    }

    printf("Memory Attached At %X\n", (int)(intptr_t) shared_memory );
    shared_stuff = (struct share_use_st *) shared_memory;

    while (running) {
        while (shared_stuff -> writen_by_you == 1)  {
            sleep(1000);1
            printf("waiting for client ...\n");
        }
        printf("Enter some text: \n");
        fgets(buffer , BUFSIZ , stdin);

        strncpy(shared_stuff-> some_text , buffer , TEXT_SZ);
        shared_stuff -> writen_by_you = 1;
        if (strncmp(buffer , "end" , 3) == 0) {
            running = 0;
        }
    }
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n" );
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

    return 0;
}
