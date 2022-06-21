/*
    一般情况下 main 函数创建的成为主线程
    
    
    #include <pthread.h>
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
        - 创建一个子线程
        @thread: 传出, 成功后 被写入
        @attr: 设置的线程的属性，一般使用默认值 NULL
        @start_routine: 函数指针，子线程需要处理的逻辑代码，回调函数
        @arg: 给第三个参数使用
        @return : 0 / +errNum, 获取的方式不太一样
                不能用 perror 用 strerror(int errnum)
*/
#include <cstring>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *callback(void *arg) {
    printf("child theread ...\n");
    // 这样子来获取参数
    printf("arg value %d \n", *(int *) arg);
    return nullptr;
}

int main() {
    pthread_t tid;

    // 传入参数
    int num = 10;

    int ret = pthread_create(&tid, nullptr, callback, (void *) &num);
    if (ret != 0) {
        char *errstr = strerror(ret);
        printf("error : %s", errstr);
    }

    for (int i = 0; i < 3; i++) {
        printf("%d\n", i);
        sleep(1);
    }

    return 0;
}