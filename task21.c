#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// от кого приходит ctrl c
//почему нельзя использовать perror и printf

static int cnt = 0;

char int_to_char(int num) {
    return num + '0';
}

int num_len(int num) {
    int len = 0;
    while (num != 0) {
        len++;
        num /= 10;
    }
    return len;
}

void int_to_str(int num, char *buf, int len) {
    char *p = buf + len;

    *p = '\0';
    p--;

    while (num != 0) {
       *p = int_to_char(num % 10);
       num /= 10;
       p--;
    }
}

void quit() {
    int len = num_len(cnt);
    char buf[len + 1];
    int_to_str(cnt, buf, len);

    write(2, "\n", 1);
    write(2, buf, len + 1);
    write(2, "\n", 1);

    exit(2);
}

void print() {
    write(2, "\a", 1);
    cnt++;
}

_Noreturn void action() {
    struct sigaction act2, act3;
    sigset_t sigset1;

    sigemptyset(&sigset1);
    sigaddset(&sigset1, SIGINT);

    act2.sa_handler = quit;
    act3.sa_handler = print;

    sigprocmask(SIG_UNBLOCK, &sigset1, NULL);

    if (sigaction(SIGQUIT, &act2, NULL) == -1){
        write(2,"sigaction error\n", 17);
    }

    if (sigaction(SIGINT, &act3, NULL) == -1){
        write(2,"sigaction error\n", 17);
    }

    write(2, "\nalarm!\n", 8);

    print();

    while (1) {
        pause();
    }
}

int main() {
    struct sigaction act1;

    char buf[3];
    int_to_str(10, buf, 2);


    act1.sa_handler = action;

    sigfillset(&act1.sa_mask);
    sigdelset(&act1.sa_mask, SIGQUIT);

    if (sigaction(SIGINT, &act1, NULL) == -1) {
        write(2,"sigaction error\n", 17);
    }

    write(2, "sleeping\n", 9);
    pause();

    return 0;
}




