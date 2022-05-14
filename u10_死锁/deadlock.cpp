#include <cstdio>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int tickets = 100;
void *sell_ticket(void *arg) {
    // ##############
    while (true) {
        // 2. 重复加锁 一张都没卖出
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex);
        bool ok = tickets > 0 ? true : false;
        if (ok) printf("%ld is selling %d ticket\n", pthread_self(), tickets--);

        // 1. 忘记释放锁 只卖出一张票
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
