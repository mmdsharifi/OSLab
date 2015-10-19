/*
    Aouther : Mohammad Sharifi
    StuNo: 911122115
    Mon - 19 Oct 2015
    git repo:
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FIFO_FILE   "MYFIFO"

int main(void)
{
    FILE *fp;
    int i = 1;
    char readbuffer[80];

    while ( 1 ) {
        fp = fopen(FIFO_FILE , "r");
        fgets(readbuffer, 80, fp);
        printf("From P2 : Received string: %s\n", readbuffer);
        while (readbuffer[i]) {

            if ( i % 2 == 1) {
                readbuffer[i] = tolower(readbuffer[i]);

            }
            i++;
        }
        printf("P3 : %s\n", readbuffer );
        fclose(fp);
        break;
    }
    return 0;
}

/*
 documents:

 #FIFO
 =======================

*/
