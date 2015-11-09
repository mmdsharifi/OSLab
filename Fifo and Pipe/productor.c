#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/myfifo"
#define TEN_MEG (1024)

int main(void) {
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    char buffer[BUFSIZ + 1];
    int bytes_sent = 0;
    if (access(FIFO_NAME , F_OK) == -1) {
        res = mkfifo(FIFO_NAME , 0777);
        if ( res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME );
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY \n",  getpid());
    pipe_fd = open( FIFO_NAME , open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd );

    if (pipe_fd != -1) {
        while (bytes_sent < TEN_MEG) {
            res = write( pipe_fd , buffer  , BUFSIZ);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe\n" );
                exit(EXIT_FAILURE);
            }
            bytes_sent += res;
            printf("Process %d Write ... \n", res );
        }
        (void)close(pipe_fd);
    }
    else{
        exit(EXIT_SUCCESS);
    }
    return 0;
}
