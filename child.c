#include <stdio.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char **argv) {
    char buff[100];
    size_t cnt;

    while (1) {
        cnt = read(0, buff, 100);

        for (int i = 0; i < cnt; ++i) {
            buff[i] = toupper(buff[i]);
        }

        write(1, buff, cnt);
    }

}




