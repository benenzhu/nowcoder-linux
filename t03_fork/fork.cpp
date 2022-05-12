/*
    #include <unistd.h>

    pid_t fork(void);
        创建子进程
        返回值： 
            返回两次
            父进程 返回 pid 
            子进程 返回 0
            通过fork的返回值来区分父子进程

*/

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
        printf("i am child pid: %d  ppid: %d\n", getpid(), getppid());
    } else {
        perror("error of fork");
    }

    for (int i = 0; i < 3; i++) {
        printf("i : %d  pid : %d\n", i, getpid());
        sleep(1);
    }

    return 0;
}