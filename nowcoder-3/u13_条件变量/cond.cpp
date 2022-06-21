/*
NAME
       pthread_cond_destroy, pthread_cond_init - destroy and initialize condition variables

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_destroy(pthread_cond_t *cond);
       int pthread_cond_init(pthread_cond_t *restrict cond,
              const pthread_condattr_t *restrict attr);
       pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
######################################################################
NAME
       pthread_cond_timedwait, pthread_cond_wait - wait on a condition

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_timedwait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex,
              const struct timespec *restrict abstime);
            - 等待 指定的时间 之后就不阻塞了
       int pthread_cond_wait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex);
#######################################################################
NAME
       pthread_cond_broadcast, pthread_cond_signal - broadcast or signal a condition

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_broadcast(pthread_cond_t *cond);
            - 广播 唤醒所有的
       int pthread_cond_signal(pthread_cond_t *cond);
            - 只有一个？？
*/

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <type_traits>
#include <unistd.h>

struct Node {
    int num;
    struct Node *next;
};
struct Node *head = nullptr;

// 互斥量解决同步问题
pthread_mutex_t mu;
pthread_cond_t cond;
int cnt = 0;
void *produce(void *arg) {

    while (1) {

        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        pthread_mutex_lock(&mu);
        newNode->next = head;
        head = newNode;
        newNode->num = ++cnt;
        printf("++node : %d, tid : %ld\n", newNode->num, pthread_self());
        // 只要生产一个就通知一下
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mu);
        usleep(100);
    }
    return nullptr;
}

void *consume(void *arg) {
    while (1) {
        pthread_mutex_lock(&mu);
        struct Node *tmp = head;
        if (head != nullptr) {
            head = head->next; // 这个出错了 head已经被free掉了
            printf("--node : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mu);
            usleep(100);
        }else {
            // 没有数据，需要等待
            pthread_cond_wait(&cond, &mu);
            pthread_mutex_unlock(&mu);
        }

    }
    return nullptr;
}
int main() {
    pthread_mutex_init(&mu, nullptr);
    pthread_cond_init(&cond, nullptr);
    pthread_t ptids[5], ctids[5];
    for (auto &pid : ptids) {
        pthread_create(&pid, nullptr, produce, nullptr);
    }
    for (auto &pid : ctids) {
        pthread_create(&pid, nullptr, consume, nullptr);
    }
    for (int i = 0; i < 5; i++) {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }
    while (1) {
        sleep(10);
    }
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mu);
    pthread_exit(nullptr);
}
