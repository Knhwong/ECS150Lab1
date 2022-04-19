#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

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
        printf("Received signal %d (%s)", signum, arr[signum]);
}

int main(int argc, char* argv[]){
    
    for(int i = 0; i < 32; i++){
        signal(i, sigHandler);
    }

    while(1){
        sleep(1);
        printf("Process is running\n");
    }

    //in another terminal window   kill signal-number pid

}
