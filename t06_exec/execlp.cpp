#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
int main() {
    /*
    int execlp(const char *path, const char *arg, ...)
        !!!!! 可以在环境变量中进行查找
        @path 需要执行的路径的名称
        @arg... 执行程序的参数列表
            @arg0: 文件名称
            @arg... 参数最后需要以null结束
        @ret: 调用失败是 -1 
            调用成功没有返回值 因为被替换掉了
    */

    // 创建一个子进程
    pid_t pid = fork();

    if (pid > 0) {
        printf("i am a parent process : %d\n", getpid());
        sleep(1);
    } else {
        // 直接指定不会运行的
        execlp("hello", "ps", "aux", NULL);
        printf("i am child process : %d\n", getpid());
    }
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }
    return 0;
}
