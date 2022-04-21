#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char **argv) {
    pid_t cpid;
    int status;

    cpid = fork();
    switch (cpid) {
        case -1:
            perror("Error process call");
            break;
        case 0:
            /*child process*/
            execvp(argv[1], argv + 1);
            perror("exec can't run program");
            break;
        default:
            //if (kill(cpid, SIGABRT) == -1)
              //  printf("signal send error");

            if (wait(&status) == -1)
                printf("wait call error");

            if (WIFEXITED(status))
                printf("\nchild end status is %d\n", status);
            else {
                printf("child was terminated by signal %d\n", status);
            }
    }

    return 0;
}


