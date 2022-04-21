#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv) {
    pid_t cpid;
    int status;

    sigset_t sigset;
    sigfillset(&sigset);
    sigaddset(&sigset, SIGQUIT);
    sigdelset(&sigset, SIGINT);

    struct sigaction act;

    act.sa_mask = sigset;
    act.sa_flags = SIG_DFL;


    sigaction(SIGINT, )



    //cpid = fork();
    return 0;
}




