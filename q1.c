#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void sigHandler(int signum){
    printf("exit\n");
    exit(0);
}

int main(int argc, char* argv[], char* envp[]){
    // less than 3 arg 
    if (argc < 3){
        printf("Need 3 arguments\n");
        return 0;
    } 

    // s is not a number
    bool sIsDigit = true;
    for (int i = 0; i < strlen(argv[1]); i++){
        if(!isdigit(argv[1][i])){
            sIsDigit = false;
            break;
        }
    }
    
    if(!sIsDigit){
        printf("Number of seconds should be an integer\n");
        return 0;
    }

    int s = atoi(argv[1]);

    // s is negative
    if (s < 0){
        printf("Negative number of seconds\n");
        return 0;
    }

    int forkVal = fork();

    if (forkVal < 0){ // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (forkVal == 0){ //child process
        //newarg[0] =argv[2];
        printf("child\n");
        execve(argv[1],argv+2,envp);
        perror("execve");
        printf("child\n");
    }
    else { //parent process
        //kill process after s seconds
        signal(SIGCHLD,sigHandler);
        sleep(s);
        // system alarm: set up with s, return sigalarm in s second
        kill(forkVal, SIGTERM); 
        wait(NULL);
        
    }
    return 1;

} 