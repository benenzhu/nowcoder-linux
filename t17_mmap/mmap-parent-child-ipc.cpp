/*
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/*
    使用 mmap 实现 IPC
    1. 有关系的进程：   
        - 还没有子进程的时候，
            - 通过唯一的父进程，先创建内存映射区
        - 有了以后，创建子进程
        - 父子共享
    2. 没有关系的进程间通信
        - 准备一个大小不是0的磁盘文件
        通过内存进行读写
    内存映射区通信是非阻塞的

*/
int main() {
    /*
    void *mmap(void *addr, size_t len, int prot, int flags, int fd, __off_t offset)
    @return: 首地址, 失败返回 MAP_FAILED
        @addr: 首地址 NULL 自动选择
        @len: 长度, 不能为0 使用文件的长度
                获取文件长度 stat / lseek
        @prot:  内存映射区的操作权限
                pages 可以被怎么样。。。 
                PROT_READ | PROT_WRITE 
                要操作映射区，必须有读的权限 
        @flags: 
                MAP_SHARED / MAP_PRIVATE
                shared话 映射会自动同步
                private话 原来的文件不会同步， 会创建一个新的文件 copy on write
        @fd:   
                需要映射的文件描述符
                通过 open 得到, 大小不能为 0
                权限必须大于 prot的权限  
                PROT_READ | PROT_WRITE
        @offset:
                映射时候的偏移量 off ~ off + len 的文件
                必须是4k的整数倍
    int munmap(void *addr, size_t length);
        @addr 地址
        @len 和 mmap 的 size是一样的
    */
    int fd = open("test.txt", O_RDWR);
    int size = lseek(fd, 0, SEEK_END); // 获取文件的大小

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap err");
        exit(-1);
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid > 0) {
        strcpy((char *) ptr, "nihao a son!!!");
    } else {
        char buf[64];
        strcpy(buf, (char *) ptr);
        printf("son readed data : %s\n", buf);
    }
    munmap(ptr, size);

    return 0;
}