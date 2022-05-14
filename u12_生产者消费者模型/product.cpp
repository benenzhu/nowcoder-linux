#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

// 容器 用链表 可以无限的加？
// 5个生产者 和 5个消费者

struct Node{
    int num;
    struct Node* next;
};


struct Node * head = nullptr;


int cnt = 0;
void * produce(void * arg){

    while(1){
        struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode ->next = head;
        head = newNode;
        newNode->num = ++cnt;
        printf("add node, num : %d, tid : %ld\n",newNode->num, pthread_self());
        usleep(100);
    } 
    return nullptr;
}


void * consume(void * arg){
    while(1){
        struct Node * tmp = head;
        head = head->next;
        printf("consume %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        usleep(100);
    }
    return nullptr;
}
int main() {

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

    // while (1) {
    //     sleep(10);
    // }
    pthread_exit(nullptr);

}
