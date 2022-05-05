#include <stdio.h>


int main(int argc, char **argv) {
    char buf[100];
    FILE *pipe_des = popen("wc", "w");
    //fscanf(pipe_des, "%s", buf);
    fprintf(pipe_des, "text");

    pclose(pipe_des);
    return 0;
}



