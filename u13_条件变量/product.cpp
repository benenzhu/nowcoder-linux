#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

// 容器 用链表 可以无限的加？
// 5个生产者 和 5个消费者

struct Node {
    int num;
    struct Node *next;
};
struct Node *head = nullptr;

// 互斥量解决同步问题
pthread_mutex_t mu;

int cnt = 0;
void *produce(void *arg) {

    while (1) {

        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        pthread_mutex_lock(&mu);
        newNode->next = head;
        head = newNode;
        newNode->num = ++cnt;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mu);
        usleep(100);
        
    }
    return nullptr;
}

void *consume(void *arg) {
    while (1) {
        pthread_mutex_lock(&mu);
        struct Node *tmp = head;
        if(head == nullptr){
            pthread_mutex_unlock(&mu); // 这样子浪费资源了。。。
            usleep(100);
            continue;
        } 
        head = head->next; // 这个出错了 head已经被free掉了
        printf("consume %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mu);
        usleep(100);
    }
    return nullptr;
}
int main() {
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
    pthread_mutex_destroy(nullptr);
    pthread_exit(nullptr);
}
