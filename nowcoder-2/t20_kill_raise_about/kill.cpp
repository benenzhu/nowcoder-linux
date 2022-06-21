
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    /*
    kill(__pid_t pid, int sig);
        - 给 pid或者进程组 发送信号 
        @pid 
            >0 指定的进程
            =0 当前的进程组
            -1 所有有权限的
            <-1 进程组里面的所有 
        @sig: 信号宏
    e.g.
        kill(getppid(), 9);
        kill(getpid(), 9);

    int raise(int sig);
        - 给当前的进程发送信号
        @sig
        @return 
            0
            nonzero: fail
    
    void abort(void)
        发送一个 SIGABRT 信号给当前进程
    */
    pid_t pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 10; i++) {
            printf("child process %d\n", i);
            sleep(1);
        }
    } else if (pid > 0) {
        printf("parent process\n");
        sleep(2);
        puts("kill the child now");
        // 抢占cpu的资源 所以执行的次数不一定...
        kill(pid, SIGINT);
        wait(NULL);
    }
    return 0;
}
