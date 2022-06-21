/*
    以下信号集相关的函数都是对自定义的信号集进行操作

    int sigemptyset(sigset_t *set);
        - 清空置0
        - @set,传出
        - @return: 0 / -1

    int sigfillset(sigset_t *set);
        - 所有的标志位置为1
        - @set, 传出
        - @return 0 / -1

    int sigaddset(sigset_t *set, int signum);
        - 置1 阻塞
        - @set 传出
        - @signum 需要设置的信号
        - @return 0 / -1

    int sigdelset(sigset_t *set, int signum);
        - 置0 
        - @set
        - @signum
        - @return 0 / -1

    int sigismember(const sigset_t *set, int signum);
        - 判断是否阻塞
        - @set
        - @signum
        - @return:
            1: 阻塞
            0: 不阻塞
            -1: 失败

*/

#include <csignal>
#include <cstdio>
int main() {
    sigset_t set;
    // 清空信号集的内容
    sigemptyset(&set);
    int ret = sigismember(&set, SIGINT);
    if (ret == 0) {
        puts("SigInt不阻塞");
    } else if (ret == 1) {
        puts("SigInt阻塞");
    }

    // 添加几个信号
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigismember(&set, SIGINT);
    if (ret == 0) {
        puts("SigInt不阻塞");
    } else if (ret == 1) {
        puts("SigInt阻塞");
    }

    ret = sigismember(&set, SIGQUIT);
    if (ret == 0) {
        puts("SIGQUIT 不阻塞");
    } else if (ret == 1) {
        puts("SIGQUIT 阻塞");
    }

    // 删除信号
    sigdelset(&set, SIGQUIT);

    ret = sigismember(&set, SIGQUIT);
    if (ret == 0) {
        puts("SIGQUIT 不阻塞");
    } else if (ret == 1) {
        puts("SIGQUIT 阻塞");
    }

    return 0;
}