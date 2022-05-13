#include <stdio.h>
#include <unistd.h>
/*
    time = 内核时间 + 用户时间 + 消耗时间
    进行文件IO操作比较浪费时间

    定时器：与进程的状态无关，自然定时法，无论处于什么状态，alarm都会计时
*/
int main() {
    alarm(1);
    int i = 0;
    while (1) {
        i++;
        while (i % 10000 == 0) printf("%d\n", i++);
    }
}