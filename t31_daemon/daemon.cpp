/*
    写一个守护进程， 

*/

#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int cnt = 0;
/*
       #include <time.h>
       time_t time(time_t *t);
*/
void work(int sig_num) {
    // 获取系统时间 写入磁盘
    auto tm = time(nullptr);
    // 转换格式
    struct tm *loc = localtime(&tm);
    // char buf[1024];
    // sprintf(buf, "%d-%d-%d %d:%d:%d\n", loc->tm_year, loc->tm_mon, loc->tm_mday,
    // loc->tm_hour, loc->tm_min, loc->tm_sec);
    // puts(buf);
    char *str = asctime(loc);
    // 必须用追加数据
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd, str, strlen(str));
    close(fd);
}
int main() {
    //1. 创建子进程 退出夫进程
    pid_t pid = fork();
    if (pid > 0) {
        exit(0);
    }

    // 2. 子进程重新创建会话；
    setsid();

    // 3. 设置掩码
    umask(022);

    // 4. 更改工作目录
    // chdir("/");

    // 5. 关闭 重定向文件描述符
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    // 6. 业务逻辑
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);
    // 捕捉定时信号
    sigaction(SIGALRM, &act, nullptr);

    struct itimerval val;
    val.it_interval.tv_sec = 2;
    val.it_value.tv_sec = 2;
    val.it_interval.tv_usec = 0;
    val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &val, nullptr);

    while (1) {
        sleep(10);
    }
    return 0;
}