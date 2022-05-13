/*
    匿名映射， 不需要文件实体进行的映射
*/
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    // 创建匿名映射区
    int len = 4096;
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    // 父子进程通信
    pid_t pid = fork();
    if (pid > 0) {
        strcpy((char *) ptr, "hello world zhuzhu\n");
        wait(NULL);
    } else {
        sleep(1);
        printf("%s\n", (char *) ptr);
    }

    int ret = munmap(ptr, len);
    if (ret == -1) {
        perror("unmap failed");
    }

    return 0;
}