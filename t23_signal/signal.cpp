/*

    #include <signal.h>

    typedef void (*sighandler_t)(int);

    sighandler_t signal(int signum, sighandler_t handler);
        功能： 设置某个信号的捕捉行为
        @return:
            成功：返回上一次的地址
            失败：返回 SIG_ERR, 设置错误号
        @signum: 
        @handler
            - SIG_IGN
            - SIG_DFL
            - 回调函数
                需要提前实现和准备好的 
                当发生事件时候 引起会掉
        SIGKILL SIGSTOP 不能被捕捉和忽略

*/
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// void sighandler_t(int);
void my_wait(int num) { // int 表示编号是什么

    printf("捕捉到了信号 %d\n", num);
}
int main() {

    auto ret_sig = signal(SIGALRM, my_wait);
    if (ret_sig == SIG_ERR) {
        perror("signal error");
        exit(-1);
    }

    struct itimerval new_value, old_value;
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;
    int ret = setitimer(ITIMER_REAL, &new_value, &old_value); // 非阻塞的东西
    if (ret == -1) {
        perror("setitimer error");
        exit(0);
    }
    puts("timer start");
    for (int i = 1;; i++) {
        sleep(1);
        printf("time now : %d\n", i);
    }

    return 0;
}
