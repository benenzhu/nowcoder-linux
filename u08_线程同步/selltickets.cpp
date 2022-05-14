/*
    使用多线程 实现 sell
    有3个窗口， 一共100张票, 并发的卖票
    */

#include <cstdio>
#include <pthread.h>
#include <unistd.h>

int tickets = 100;
void *sell_ticket(void *arg) {
    while (tickets > 0) {
        usleep(3000);
        printf("%ld is selling %d ticket\n", pthread_self(), tickets--);
    }
    return nullptr;
}
int main() {
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, nullptr, sell_ticket, nullptr);
    pthread_create(&tid2, nullptr, sell_ticket, nullptr);
    pthread_create(&tid3, nullptr, sell_ticket, nullptr);

    // 回收子线程的资源
    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);

    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    // exit main
    pthread_exit(nullptr);

    // 创建3个子线程

    return 0;
}
