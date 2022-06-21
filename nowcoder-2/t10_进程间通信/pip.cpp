#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    /*
       int pipe(int pipefd[2]);
       
       pipefd 是传出 [0] [1]
       成功 0 失败 -1
       管道默认是阻塞的
    */
    int pipefd[2];
    int fd = pipe(pipefd);
    if (fd == -1) {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0) {
        // 子进程 // 写入
        while (1) {
            char buf[] = "i am child";
            // sleep(1);
            write(pipefd[1], buf, strlen(buf));
            printf("write of child %d : %s\n", strlen(buf), buf);

            char buf2[1024] = {0};
            int len = read(pipefd[0], buf2, sizeof(buf2));
            printf("child recv %d: %s\n", len, buf2);
        }

    } else if (pid > 0) {
        char buf[1024] = {0};
        while (1) {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent recv %d: %s\n", len, buf);
            bzero(buf, sizeof(buf));
            // sleep(1);
            char buf2[] = "i am parent";
            write(pipefd[1], buf2, sizeof(buf2));
            printf("write of parent %d : %s\n", strlen(buf2), buf2);
        }
    }

    return 0;
}
