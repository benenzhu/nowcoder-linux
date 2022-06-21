#include <cstdio>
#include <unistd.h>
int main() {
    /*
    unsigned int alarm(unsigned int seconds);
        - 设置闹钟 函数调用：sec, 开始倒计时， 当为0时候， 发送信号
            SIGALARM
        @sec:倒计时时长 秒
            =0 无效 或者 取消原来的
        @return:
            - 之前没有定时器：返回0
            - 之前有定时器：返回剩余的时间
            

    SIGALARM: 默认中止当前的进程， 每一个进程只有唯一一个alarm 
        alarm(10);
    */
    int sec = alarm(5);
    printf("seconds = %d\n", sec);
    sleep(2);
    sec = alarm(5);
    printf("seconds = %d\n", sec);
    while (1) {
        printf("waiting\n");
        sleep(1);
    }
    return 0;
}