/*
    #include <signal.h>

    int sigaction(int signum, const struct sigaction *act,
                    struct sigaction *oldact);
        - 检查 / 设置信号的action
        - @signum 
        - @act : 捕捉掉信号的处理动作
                struct sigaction {
                    // 处理函数
                    void     (*sa_handler)(int);
                    // 不常用
                    void     (*sa_sigaction)(int, siginfo_t *, void *);
                    // 临时阻塞信号集，捕捉过程中会阻塞
                    sigset_t   sa_mask;
                    // SA_SIGINFO // 0
                    int        sa_flags; // 指定用第几个函数
                    // 废弃掉了
                    void     (*sa_restorer)(void);
                };
        - @oldact
        - @return: 0 / -1
        // 每个信号只能标记一次信号的状态是什么
        // 后面的信号是支持排队的？
*/
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void my_wait(int num) { // int 表示编号是什么
    printf("捕捉到了信号 %d\n", num);
}
int main() {

    struct sigaction act;

    act.sa_flags = 0;
    act.sa_handler = my_wait;
    sigemptyset(&act.sa_mask);
    auto sig_ret = sigaction(SIGALRM, &act, nullptr);
    // if (ret_sig == SIG_ERR) {
    //     perror("signal error");
    //     exit(-1);
    // }

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