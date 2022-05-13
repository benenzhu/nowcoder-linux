#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    /*
        pid_t  waitpid(pid_t   pid,   int   *stat_loc,   int
       options);
            功能：回收指定进程的子进程，可以设定是否阻塞        
            @pid 
                >  0 : 具体的
                =  0 : same group 一般是最初的那个进程？
                = -1 : 所有的子进程 相当于 wait() ?
                < -1 : 某个gid  里面的东西
            @options:
                0 : 阻塞
                WCONTINUED 
                WNOHANG
                WUNTRACED
            return:
                >0 : id
                =0 : options = WNOHANG, 表示还有子进程  
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
            // int ret = waitpid(-1, &st, 0); // 不是要阻塞么？
            int ret = waitpid(-1, &st, WNOHANG); // 不是要阻塞么？

            if (ret == -1) {
                puts("all done");
                return 0;
            } else if (ret == 0) {
                printf("still have let's wait\n");
            } else {
                if (WIFEXITED(st)) {
                    printf("exit normal by %d:\n", WEXITSTATUS(st));

                } else if (WIFSIGNALED(st)) {
                    printf("killed by: %d\n", WTERMSIG(st));
                }
                printf("child die pid = %d status %x\n", ret, st);
            }

            sleep(1);
        }
    } else if (pid == 0) {
        printf("i am child pid = %d\n", getpid());
        sleep(2);
        exit(0);
    }
    return 0;
}