#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigHandler(int signum){
        char* arr[] = {NULL, "SIGHUP", "SIGINT"};
        printf("Received signal %d (%s)", signum, arr[signum]);
}

int main(int argc, char* argv[]){
    
    for(int i = 0; i < 32; i++){
        signal(i, sigHandler);
    }

    while(true){
        prinf("Hello World\n");
        
    }

    //in another terminal window    KILL -SIGKILL pid

}