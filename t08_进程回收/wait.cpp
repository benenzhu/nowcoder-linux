#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    /*
        pid_t wait(int *status);
            功能：等待任意一个子进程结束，回收资源 
            参数：int 退出时候的状态信息 
                传出参数
            成功： 被回收的 pid
                -1 otherwise
                    // all end
                    // error
        调用 会阻塞掉 什么状态？ 
        如果没有子进程了
    */
    pid_t pid;

    for (int i = 0; i < 5; i++) {
        pid = fork();        // 后面的好像会出错是吧 应该看一下fork的返回值的
        if (pid <= 0) break; // 子进程直接不继续了
    }

    if (pid > 0) {
        while (1) {
            printf("parent, pid = %d\n", getpid());
            int st;
            int ret = wait(&st); // 不是要阻塞么？
            if (WIFEXITED(st)) {
                printf("exit normal by %d:\n", WEXITSTATUS(st));

            } else if (WIFSIGNALED(st)) {
                printf("killed by: %d\n", WTERMSIG(st));
            }
            printf("child die pid = %d status %x\n", ret, st);

            if (ret == -1) {
                puts("all done");
                return 0;
            }
            sleep(1);
        }
    } else if (pid == 0) {
        printf("i am child pid = %d\n", getpid());
        // while (1)
        // ;
        exit(0);
    }
    return 0;
    // 创建5个子进程 fork
    // 回收掉
}