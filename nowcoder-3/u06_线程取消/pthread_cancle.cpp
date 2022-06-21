/*
NAME
    pthread_cancel - send a cancellation request to a thread
        取消线程 让线程中止
        有一定的条件 state / type
        清理垃圾啊等等
SYNOPSIS
    #include <pthread.h>
    int pthread_cancel(pthread_t thread);


    pthread_setcancelstate
pthread_setcanceltype asynchronous deferred（遇到cancellation point时候, 有很多种）
    大致是执行到系统调用的时候取消
*/

#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

void *callback(void *args) {
    for (int i = 0; i < 5; i++) {
        printf("child : %d\n", i);
    }
    sleep(1);
    printf("child thread id : %ld\n", pthread_self());
    return nullptr;
}
int main() {
    pthread_t tid; // 线程池 后面说
    int ret = pthread_create(&tid, nullptr, callback, nullptr);
    if (ret != 0) {
        char *errstr = strerror(ret);
        puts(errstr);
    }

    printf("tid : %ld, main : %ld\n", tid, pthread_self());
    // 输出一下主线程和子线程的id

    //取消线程
    pthread_cancel(tid);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    // pthread_detach(tid);

    // // 尝试连接：
    // ret = pthread_join(tid, nullptr);
    // if (ret != 0) {
    //     char *errstr = strerror(ret); // 会报错 没有调用成功
    //     puts(errstr);
    // }

    pthread_exit(nullptr);
}
