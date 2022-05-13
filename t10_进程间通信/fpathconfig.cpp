#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main() {

    /*
       long fpathconf(int fd, int name);
       long pathconf(char *path, int name);
    */
    int pipefd[2];
    int fd = pipe(pipefd);

    // 获取管道的大小
    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);

    printf("pipe size : %ld\n", size);
    return 0;
}