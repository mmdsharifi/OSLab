/*
    Aouther : Mohammad Sharifi
    StuNo: 911122115
    Mon - 19 Oct 2015
    git repo:
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <linux/stat.h>
#include <fcntl.h>

#define FIFO_FILE   "MYFIFO"

int main(void)
{
    FILE *fp;
    int fd[2] , nbytes , i=0;
    pid_t childpid;
    char string[20] ;
    char readbuffer[80];

    printf("P1:Enter a word  :\n");
    scanf("%s", string );
    pipe(fd);

    if ((childpid = fork()) == -1 ) {
        perror("fork");
        //exit(1);
    }
    if(childpid == 0)// detect on witch process at now
        {
            /* Child process closes up input side of pipe */
            close(fd[0]);
            /* Send "string" through the output side of pipe */
            write(fd[1], string, strlen(string) );
            //exit(0);
        }
        else{
            /* Parent process closes up output side of pipe */
            close(fd[1]);
            /* Read in a string from the pipe */
            nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
            while ( string[i]) {
                readbuffer[i] = toupper(string[i]);
                i++;
            }
            printf("P2: Received string: %s \n", readbuffer);
            /* Create the FIFP if it dies not exist */
            umask(0);
            mknod(FIFO_FILE , S_IFIFO|0777 , 0);
            // while ( 1 ) {
            //     fp = fopen(FIFO_FILE , "r");
            //     fgets(readbuffer , 80 , fp);
            //     fclose(fp);
            // }
            if ((fp = fopen(FIFO_FILE , "w" )) == NULL) {
                perror("fopen");
                exit(1);
            }
            fputs( readbuffer , fp );
            printf("End of writing in FIFO\n");
         }
        return 0;
}
/*
 documents:

 #Pipe:
 =======================
  fd0  fd1
 ==>= P =>=
||       ||
||       ||
 ==<= CH ==
  fd1  fd0

 Receive stream from child:  if P <- CH : Parent process must closes up (output side pipe) fd1   ,   child close fd0
 Send stram to Child      :  if P -> CH : Parent process must closes up (input side pipe)  fd0   ,   child close fd1

 more on: The Linux Programmer's Guide // chapter 6 // page 19 , 20

 #FIFO
 =======================

*/
