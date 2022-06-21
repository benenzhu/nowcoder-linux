#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int main() {
    /*
    setitimer(__itimer_which_t which, const struct itimerval *__restrict new, struct itimerval *__restrict old) 
        - 设置定时器， 可以替代 alarm 精度很高 us 可以实现周期性的定时
        @which : 定时器以什么计时
                ITIMER_REAL
                ITIMER_VIRTUAL: 用户态时间 SIGVTALRM
                ITIMER_PROF:
        @new
            struct itimerval {
                struct timeval it_interval; // next value  间隔是么
                struct timeval it_value;    // current value  延迟多长时间执行
            };

            struct timeval {
                time_t      tv_sec;         // seconds  
                suseconds_t tv_usec;        // microseconds 
            };

        过10s后， 每隔2s定时执行一次 √
        it_value    it_interval
        @old_value
            记录的上一次的定时 可以传递 NULL
        @return 普通
    */

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

    getchar();
    return 0;
}
