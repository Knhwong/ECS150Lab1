#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//With reference from https://www.techiedelight.com/print-current-date-and-time-in-c/ for printing out the date and time

void sigHandler(int signum){
        char* arr[] = {
        "Signal 0",     /*  signal 0 -- meaningless */
        "SIGHUP",       /* 1 */
        "SIGINT",
        "SIGQUIT",
        "SIGILL",
        "SIGTRAP",
        "SIGABRT",
        "SIGEMT",
        "SIGFPE",
        "SIGKILL",
        "SIGBUS",       /* 10 */
        "SIGSEGV",
        "SIGSYS",
        "SIGPIPE",
        "SIGALRM",
        "SIGTERM",
        "SIGUSR1",
        "SIGUSR2",
        "SIGCHLD",
        "SIGCONT",
        "SIGTSTP",      /* 20 */
        "SIGTTIN",
        "SIGTTOU",
        "SIGSTOP",
        "SIGXCPU",
        "SIGXFSZ",
        "SIGVTALRM",
        "SIGPROF",
        "SIGWINCH",
        "SIGPOLL",
        "SIGUSR1",      /* 30 */
        "SIGUSR2"
        };

        time_t curTime;
        time(&curTime);
        char* outputTime = ctime(&curTime);
        outputTime[strlen(outputTime)-1] = '\0';

        printf("%s ", outputTime);
        printf("Received signal %d (%s)\n", signum, arr[signum]);
}

int main(int argc, char* argv[]){
    
    for(int i = 0; i < 32; i++){
        signal(i, sigHandler);
    }

    while(1){
        sleep(1);
        printf("%d Process is running\n", getpid());
    }

    //in another terminal window   kill signal-number pid

}
