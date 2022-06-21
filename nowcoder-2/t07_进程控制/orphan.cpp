#include <stdio.h>
#include <unistd.h>
int main() {

    // 创建子进程
    pid_t pid = fork();

    // 判断进程是什么
    if (pid > 0) {
        printf("pid : %d\n", pid);
        printf("i am parent pid: %d  ppid: %d\n", getpid(), getppid());
    } else if (pid == 0) {
        sleep(1);
        // 这个ppid 应该是 1 归属于 init 了
        printf("i am child pid: %d  ppid: %d\n", getpid(), getppid());
    } else {
        perror("error of fork");
    }

    // for (int i = 0; i < 3; i++) {
    //     printf("i : %d  pid : %d\n", i, getpid());
    //     sleep(1);
    // }

    return 0;
}