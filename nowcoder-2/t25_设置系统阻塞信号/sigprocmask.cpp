/*
    sigprocmask(int how, const sigset_t *__restrict set, sigset_t *__restrict oset)
        - 将自定义信号集设置到内核中
        - @how: 如何处理信号
                SIG_BLOCK: 阻塞  
                    mask | set
                SIG_UNBLOCK: 不阻塞 解除阻塞 
                    mask &= ~set
                SIG_SETMASK: 覆盖内核中原来的值
                    mask = set
        - @set: 已经初始化好的用户自定义的set集合 
        - @oset:
        - @return: 
            0: success
            -1: fail

        
    int sigpending(sigset_t *set) 
        - 获取未决信号集
        - @set 传出 保存的是内存中未决信号集中的信息
*/

// 编写一个程序 把所有的常规信号的未决状态打印出来 1 ~ 31
// 设置一些信号阻塞掉，用键盘产生这些信号
#include <csignal>
#include <cstdio>
#include <unistd.h>
int main() {

    // 设置 2,3 ^c ^\ //
    sigset_t set;
    // 清空信号集的内容
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    //
    sigprocmask(SIG_BLOCK, &set, nullptr);
    int num = 0;
    while (1) {
        // 获取
        sigset_t pendingset;
        sigpending(&pendingset);
        printf("now is %d ", num++);
        for (int i = 1; i < 32; i++) {
            if (sigismember(&pendingset, i) == 1) {
                printf("1");
            } else if (sigismember(&pendingset, i) == 0) {
                printf("0");
            } else {
                perror("sigismember");
            }
        }
        puts(" zhu");
        sleep(1);
        if (num == 10) {
            sigprocmask(SIG_UNBLOCK, &set, nullptr);
        }
    }
}