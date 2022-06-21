/*
    1. 子进程结束
    2. 子进程暂停
    3. 子进程继续运行
    默认忽略该信号


    可以解决僵尸进程的问题
*/

#include <csignal>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void my_wait(int num) { // int 表示编号是什么
    printf("捕捉到了信号 %d\n", num);
    // 回收资源
    while (1) {
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret > 0) {
            printf("child die, pid = %d \n", ret);
        } else if (ret == 0) {
            // 说明还有子进程活着
            puts("还有子进程活着");
            break;
        } else if (ret == -1) {
            // 没有子进程了
            puts("没有子进程了");
            break;
        }
    }
}
int main() {

    // 先设置阻塞
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, nullptr);
    pid_t pid;
    for (int i = 0; i < 20; i++) {
        pid = fork();
        if (pid == 0) break;
    }

    if (pid > 0) {
        // 捕捉子进程的sigchld信号

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = my_wait;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL); // 还没有注册成功呢， 子进程可能就已经结束了
        // 然后接触阻塞
        sigprocmask(SIG_UNBLOCK, &set, nullptr);
        while (1) {
            printf("parent process pid : %d\n", getpid());
            sleep(2);
        }
    } else if (pid == 0) {
        printf("child process pid : %d\n", getpid());
    }
}