#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    FILE* file = popen("../child", "w");
    char buff[100];
    size_t cnt;

    while (1) {
        cnt = read(0, buff, 100);
        write(file->_fileno, buff, cnt);
    }

    pclose(file);
}



