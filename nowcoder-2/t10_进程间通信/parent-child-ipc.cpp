#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
/*
    实现 ps aux | grep xxx
    子 ： ps aux 子进程结束后 重定向发送到父进程
    父 ： 获取到数据后 进行过滤 也就是重定向 stdin 和 stdout 用 dup2

*/
// 没有完全实现功能 需要进行改造一下

int main() {

    // 创建一个管道
    int fd[2];
    int ret = pipe(fd);

    if (ret == -1) {
        perror("pipe");
        exit(-1);
    }

    // 创建子进程
    pid_t pid = fork();

    if (pid > 0) {
        // 父进程
        // 关闭写端
        // 主动关闭一下
        close(fd[1]);
        // 从管道中读取
        char buf[1024] = {0};

        int len = -1;
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "out", NULL);

        // while ((len = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
        //     // 过滤数据输出
        //     printf("%s", buf);
        //     memset(buf, 0, 1024);
        // }
    } else if (pid == 0) {
        // 子进程
        // 关闭读端
        close(fd[0]);

        // 文件描述符的重定向 stdout_fileno -> fd[1]
        dup2(fd[1], STDOUT_FILENO);
        // 执行 ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    } else {
        perror("fork");
        exit(0);
    }

    return 0;
}