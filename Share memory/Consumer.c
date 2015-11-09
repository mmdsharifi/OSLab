#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <thread>
#include <mutex>
#include "data.h"

using namespace std;

mutex m;
int i = 1;
int running = 1;
void * shared_memory = (void *)0;
struct share_use_st *shared_stuff;

int shmid;





void Read(){
    // lock mutex
    m.lock();
    if (i > 10) {
        i=1;
    }
    printf("Client #%d Readed = %s \n", i , shared_stuff -> some_text);
    sleep( rand() %4 );
    shared_stuff-> writen_by_you = 0;
        if (strncmp(shared_stuff -> some_text , "end", 3)== 0 ){
            running = 0;
        }
    i++;
    m.unlock();
}
int main(){
    shmid = shmget((key_t)1234 , sizeof(struct share_use_st) , 0666 | IPC_CREAT);
    if(shmid == -1){
        fprintf(stderr, "shmget failed \n" );
        exit(EXIT_FAILURE);
    }

    srand((unsigned int) getpid());
    shared_memory = shmat(shmid , (void * )0  , 0); // Attache the Memory

    if (shared_memory == (void *) -1 ) {
        fprintf(stderr, "shmat failed \n");
        exit(EXIT_FAILURE);
    }

    printf("Memory Attached At %X\n", (int)(intptr_t) shared_memory );
    shared_stuff = (struct share_use_st *) shared_memory;
    shared_stuff -> writen_by_you = 0;

    while (running) {
        while (shared_stuff -> writen_by_you)  {
            thread client1(Read);
            thread client2(Read);
            thread client3(Read);
            thread client4(Read);
            thread client5(Read);
            thread client6(Read);
            thread client7(Read);
            thread client8(Read);
            thread client9(Read);
            thread client10(Read);
            client1.join();
            client2.join();
            client3.join();
            client4.join();
            client5.join();
            client6.join();
            client7.join();
            client8.join();
            client9.join();
            client10.join();
        }
    }



    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n" );
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid , IPC_RMID , 0) == -1) {
        fprintf(stderr, "shmid(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);


}
