#include <cstddef>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mu1, mu2;

void *workA(void *args) {
    while (1) {
        pthread_mutex_lock(&mu1);
        // usleep(10000);
        puts("work A try get mu2");
        pthread_mutex_lock(&mu2);
        puts("work A got mu2");
    }
    return nullptr;
}

void *workB(void *args) {
    while (1) {
        pthread_mutex_lock(&mu2);
        // usleep(10000);
        puts("work B try get mu1");
        pthread_mutex_lock(&mu1);
        puts("work B got mu2");
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mu1, nullptr);
    pthread_mutex_init(&mu2, nullptr);

    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, workA, nullptr);
    pthread_create(&tid2, nullptr, workB, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    pthread_mutex_destroy(&mu1);
    pthread_mutex_destroy(&mu2);

    pthread_exit(0);
}
