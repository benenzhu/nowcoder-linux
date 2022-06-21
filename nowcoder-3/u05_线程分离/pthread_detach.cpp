/*
NAME
       pthread_detach - detach a thread 
       标记为分离，当中止的时候自动释放掉 不需要其他的去join了
       分离一个已经分离的会出错
SYNOPSIS
       #include <pthread.h>
       int pthread_detach(pthread_t thread);
*/

#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

void *callback(void *args) {
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

    // 输出一下主线程和子线程的id
    printf("tid : %ld, main : %ld\n", tid, pthread_self());

    pthread_detach(tid);

    // 尝试连接：
    ret = pthread_join(tid, nullptr);
    if (ret != 0) {
        char *errstr = strerror(ret); // 会报错 没有调用成功
        puts(errstr);
    }

    pthread_exit(nullptr);

    return 0;
}
