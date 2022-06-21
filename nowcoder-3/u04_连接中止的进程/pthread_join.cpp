/*
NAME
    pthread_join - join with a terminated thread
SYNOPSIS
    #include <pthread.h>
    int pthread_join(pthread_t thread, void **retval);
        - 连接 主动回收资源  防止僵尸线程
            这个函数是阻塞的
            调用一次只能回收一个 (线程池?)
            一般在主线程中使用
        @thread: id
        @retval: exit 返回的？
*/

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int n = 1000;
void *callback(void *arg) {
    sleep(1);
    printf("child thread id : %ld\n", pthread_self());
    return (void *) &n; // == pthread_exit(nullptr);
}
int main() {

    // 创建
    // 这个 tid 是个地址嘛？
    pthread_t tid;
    int ret = pthread_create(&tid, nullptr, callback, nullptr);
    if (ret != 0) {
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }
    for (int i = 0; i < 3; i++) {
        printf("%d\n", i);
    }
    printf("main thread id : %ld tid %ld\n", pthread_self(), tid);
    int *val;

    cout << val << "地址" << endl;
    pthread_join(tid, (void **) &val);
    cout << val << "地址" << endl;
    printf("the args %d\n", *val);
    puts("回收资源成功");
    // 主线程退出 不会影响其他的线程
    pthread_exit(nullptr);
    puts("i have exit");
    return 0;
}
