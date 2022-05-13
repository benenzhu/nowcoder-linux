// 写数据文件
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    //1. 判断文件是否存在
    int ret = access("fifo1", F_OK);

    if (ret == -1) {
        printf("管道不存在，开始创建\n");
        ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(-1);
        }
    } else {
        puts("already have the pipe");
    }

    // 这句话居然也会阻塞掉， 如果这里没有读端的话
    int fd = open("fifo1", O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(-1);
    }

    for (int i = 0; i < 5; i++) {
        char buf[1024];
        sprintf(buf, "hello %d\n", i);
        printf("write data: %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}