/*

无法保证安全问题
NAME
       sem_init - initialize an unnamed semaphore
       sem_destroy - destroy an unnamed semaphore

SYNOPSIS
       #include <semaphore.h>

       int sem_init(sem_t *sem, int pshared, unsigned int value);
            @sem :
            @pshared : 进程(非0)还是线程(0）之间
            @value: 记录信号量中的值
            
       int sem_destroy(sem_t *sem);
            - 释放资源
##############################################
NAME
       sem_wait, sem_timedwait, sem_trywait - lock a semaphore

SYNOPSIS
       #include <semaphore.h>

       int sem_wait(sem_t *sem);
            -  -- 里面的value 去判断 sem 的大小来阻塞
            - 如果大于0 就 -1 然后直接返回
            - 对信号量加锁 调用一次
       int sem_trywait(sem_t *sem);

       int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
            - 
##############################################
NAME
       sem_post - unlock a semaphore
       sem_getvalue - get the value of a semaphore

SYNOPSIS
       #include <semaphore.h>

       int sem_post(sem_t *sem);
            - ++ 里面的value 这个是不会阻塞的
            - 对信号量解锁
       int sem_getvalue(sem_t *sem, int *sval);
            - 获取值



        set_t psem; 50;
        set_t csem; 0;
        producer(){
            sem_wait(&psem);
            sem_post(&csem);
        }

        consumer(){
            sem_wait(&csem);
            sem_post(&psem);
        }

*/

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include <type_traits>
#include <unistd.h>

struct Node {
    int num;
    struct Node *next;
};
struct Node *head = nullptr;

// 互斥量解决同步问题
pthread_mutex_t mu;
sem_t psem, csem;

int cnt = 0;
void *produce(void *arg) {

    while (1) {
        sem_wait(&psem);
        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        pthread_mutex_lock(&mu);
        newNode->next = head;
        head = newNode;
        newNode->num = ++cnt;
        printf("++node : %d, tid : %ld\n", newNode->num, pthread_self());
        // 只要生产一个就通知一下
        pthread_mutex_unlock(&mu);
        sem_post(&csem);
        usleep(100);
    }
    return nullptr;
}

void *consume(void *arg) {
    while (1) {
        sem_wait(&csem);
        pthread_mutex_lock(&mu);
        struct Node *tmp = head;
        head = head->next; // 这个出错了 head已经被free掉了
        printf("--node : %d, tid : %ld\n", tmp->num, pthread_self());
        --cnt;
        free(tmp);
        pthread_mutex_unlock(&mu);
        sem_post(&psem);
        usleep(100);
    }
    return nullptr;
}
int main() {
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);
    pthread_mutex_init(&mu, nullptr);
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
    sem_destroy(&psem);
    sem_destroy(&csem);
    pthread_mutex_destroy(&mu);
    pthread_exit(nullptr);
}
