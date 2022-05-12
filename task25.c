#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>

void _read(int* pipe_des) {
    char buff[100];
    size_t cnt;

    while (1) {
        cnt = read(pipe_des[0], buff, 100);

        for (int i = 0; i < cnt; ++i) {
            buff[i] = toupper(buff[i]);
        }

        write(1, buff, cnt);
    }
}

void _write(int* pipe_des) {
    char buff[100];
    size_t cnt;

    while (1) {
        cnt = read(0, buff, 100);
        write(pipe_des[1], buff, cnt);
    }
}

int main(int argc, char **argv) {
    int pipe_des[2];

    struct stat stat1;
    fstat(pipe_des[1], &stat1);

    if (S_ISCHR(stat1.st_mode)) {
        fprintf(stderr, "%d", stat1.st_mode);
    }

    if (pipe(pipe_des) == -1) {
        perror("pipe call error");
    }

    switch (fork()) {
        case 0: {
            close(pipe_des[1]);
            _read(pipe_des);
            break;
        }

        case -1: {
            perror("fork call error");
            break;
        }

        default: {
            close(pipe_des[0]);
            _write(pipe_des);
            break;
        }
    }

    return 0;
}



