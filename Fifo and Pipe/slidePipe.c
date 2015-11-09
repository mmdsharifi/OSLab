#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *read_fp;
    char input[80];
    char buffer[ BUFSIZ + 1 ];
    int chars_read;
    memset(buffer , '\0' , sizeof(buffer));
    fscanf(stdin , "%s", input );
    //printf("%s\n", input );


    read_fp = popen("tr [a-z] [A-Z] > input" , "r");

    if ( read_fp != NULL ) {
        chars_read = fread(buffer , sizeof(char) , BUFSIZ , read_fp);
        if (chars_read > 0) {
            printf("Output was:\n%s\n", buffer );
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
    return 0;
}
