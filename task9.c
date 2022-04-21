#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
            execvp("cat", argv);
            perror("exec can't run program");
        default:
            for (int i = 0; i < 10; ++i) {
                printf("...\n");
            }

            if (wait(&status) == -1)
                printf("wait call error");

            printf("...\n");

            if(WIFEXITED(status))
                printf("\n\nend status is %d\n", status);
    }

    return 0;
}

