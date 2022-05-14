/*
NAME
       pthread_mutex_destroy, pthread_mutex_init - destroy and initialize a mutex

SYNOPSIS
       #include <pthread.h>

       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
              const pthread_mutexattr_t *restrict attr);
            @mutex mutex wait to init
            @attr: realted to mutex nullptr

            - restrict : of lang C, 被修饰的指针不能由另外一个指针进行操作
                只有唯一的关键字可以操作 
       int pthread_mutex_destroy(pthread_mutex_t *mutex);
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
====================================
NAME
       pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_unlock - lock and unlock a mutex

SYNOPSIS
       #include <pthread.h>

       int pthread_mutex_lock(pthread_mutex_t *mutex);
            - blocked 
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
            - nonblock
            @return:
       int pthread_mutex_unlock(pthread_mutex_t *mutex);
            - 
*/

#include <cstdio>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int tickets = 100;
void *sell_ticket(void *arg) {
    // ##############
    while (true) {
        // 加锁
        pthread_mutex_lock(&mutex);
        bool ok = tickets > 0 ? true : false;
        if (ok) printf("%ld is selling %d ticket\n", pthread_self(), tickets--);

        // 解锁
        pthread_mutex_unlock(&mutex);
        if (!ok) break;
        usleep(3000);
    }
    // ##############
    return nullptr;
}
int main() {

    // 初始化互斥量
    pthread_mutex_init(&mutex, nullptr);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, nullptr, sell_ticket, nullptr);
    pthread_create(&tid2, nullptr, sell_ticket, nullptr);
    pthread_create(&tid3, nullptr, sell_ticket, nullptr);

    // 回收子线程的资源
    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);

    // exit main

    pthread_mutex_destroy(&mutex);
    pthread_exit(nullptr);

    // 创建3个子线程

    return 0;
}
