#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char * argv[]) {
   // printf() displays the string inside quotation
    if (argc < 3) {
        printf("Error: insufficient number of Arguments!\n");
        exit(-1);
    }

    int s = atoi(argv[1]);
    if (s < 0) {
        printf("Error: negative number given!\n");
        exit(1);
    }
    if (s == 0 && !(strcmp(argv[1], "0") == 0)) {
        printf("Error: invalid number given!\n");
        exit(-1);
    }

    int rc = fork();
    if (rc < 0) {
        printf("Error: fork failed!\n");
        exit(-1);
    } else if (rc == 0) {
        char *args[argc - 1];
        for (int i = 2; i < argc; i++) {
            args[i-2] = argv[i];
        }
        args[argc-2] = NULL;
        execvp(args[0], args);
    } else {
        sleep(s);
        kill(rc, SIGTERM);
    }
   return 0;
}