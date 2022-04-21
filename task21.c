#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define __USE_POSIX199309 1

static struct sigaction act;

void action(int a) {
    printf("add");
}

int main(int argc, char **argv) {
    pid_t cpid;
    int status;

    sigset_t sigset;
    act.sa_handler = action;


    //sigfillset(&act.sa_mask);

    sigaction(SIGINT, &act, NULL);

    raise(SIGINT);

    //cpid = fork();
    return 0;
}




