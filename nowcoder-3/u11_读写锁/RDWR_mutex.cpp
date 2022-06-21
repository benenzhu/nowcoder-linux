/*
NAME
       pthread_rwlock_destroy, pthread_rwlock_init - destroy and initialize a read-write lock object

SYNOPSIS
       #include <pthread.h>

       int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
              const pthread_rwlockattr_t *restrict attr);
       int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

============================= 
NAME
       pthread_rwlock_rdlock, pthread_rwlock_tryrdlock - lock a read-write lock object for reading

SYNOPSIS
       #include <pthread.h>

       int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
       int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
============================= 
NAME
       pthread_rwlock_trywrlock, pthread_rwlock_wrlock - lock a read-write lock object for writing

SYNOPSIS
       #include <pthread.h>

       int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
       int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);    
============================= 
NAME
       pthread_rwlock_unlock - unlock a read-write lock object

SYNOPSIS
       #include <pthread.h>

       int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

*/
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
pthread_rwlock_t rwlock;
// 创建10个线程操作全局变量
// 3 w + 7 r

int num = 1;
// 创建一个共享数据
void *write_func(void *args) {
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        num++;
        puts("###############################");
        printf("++write, tid:%ld, num:%d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(1);
    }
    return nullptr;
}

void *read_func(void *args) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("===read, tid:%ld, num:%d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(1);
    }

    return nullptr;
}

int main() {
    pthread_rwlock_init(&rwlock, nullptr);
    pthread_t wtid[3], rtid[7];
    for (auto &tid : wtid) {
        pthread_create(&tid, nullptr, write_func, nullptr);
    }
    for (auto &tid : rtid) {
        pthread_create(&tid, nullptr, read_func, nullptr);
    }

    // 设置分离
    usleep(30000);
    for (auto &tid : wtid) {
        pthread_detach(tid);
    }
    for (auto &tid : rtid) {
        pthread_detach(tid);
    }
    pthread_rwlock_destroy(&rwlock);
    pthread_exit(nullptr);
}
