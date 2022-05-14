/*
    #include <pthread.h>
    void pthread_exit(void *retval);
        - 功能：中止一个线程，在哪个线程中调用，就表示中止哪个线程
        @retval:
            需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到

    int pthread_equal(pthread_t t1, pthread_t t2);
        // 不同的操作系统 实现不一样。。。 但是linux下是一样的
*/

#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

void *callback(void *arg) {
    sleep(1);
    printf("child thread id : %ld\n", pthread_self());
    return nullptr; // == pthread_exit(nullptr);
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

    // 主线程退出 不会影响其他的线程
    pthread_exit(nullptr);
    puts("i have exit");
    return 0;
}