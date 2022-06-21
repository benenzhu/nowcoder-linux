/*
NAME
       pthread_attr_init, pthread_attr_destroy - initialize and destroy thread attributes object

SYNOPSIS
       #include <pthread.h>

       int pthread_attr_init(pthread_attr_t *attr);
       
       int pthread_attr_destroy(pthread_attr_t *attr);
=========================================
NAME
       pthread_attr_setdetachstate,  pthread_attr_getdetachstate  -  set/get  detach  state attribute in
       thread attributes object

SYNOPSIS
       #include <pthread.h>

       int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
            @attr
            @detachstate
                PTHREAD_CREATE_DETACHED
                PTHREAD_CREATE_JOINABLE
                
       int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate);
========================================
NAME
       pthread_attr_setstacksize,  pthread_attr_getstacksize  -  set/get  stack size attribute in thread
       attributes object

SYNOPSIS
       #include <pthread.h>

       int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
       int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *stacksize);
*/

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
void *callback(void *args) {
    sleep(1);
    for (int i = 0; i < 5; i++) {
        printf("child %d thread id : %ld \n", i, pthread_self());
    }
    return nullptr;
}
// 任务：设置一下线程分离的属性
int main() {
    pthread_t tid;
    // 1. 创建 & 初始化一个线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // 2. 设置属性 为什么这里设置以后没有直接detach掉 还在运行呢？ ######## ???????
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int ret = pthread_create(&tid, &attr, callback, nullptr); // 这里设置属性
    if (ret != 0) {
        char *errstr = strerror(ret);
        puts(errstr);
    }

    // 3. 获取线程栈的大小
    size_t size;
    pthread_attr_getstacksize(&attr, &size);
    printf("thread stack size %ld\n", size / 1024);

    // 输出一下主线程和子线程的id
    printf("tid : %ld, main : %ld\n", tid, pthread_self());

    // 3. 释放线程资源
    pthread_attr_destroy(&attr);
    pthread_exit(nullptr);

    return 0;
}