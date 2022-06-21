// 写数据文件
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int fd = open("fifo1", O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(-1);
    }

    while (1) {
        char buf[1024];
        bzero(buf, sizeof(buf));
        int len = read(fd, buf, sizeof(buf));
        if (len == 0) {
            puts("写完成了");
            break;
        }
        printf("recved %d: %s\n", len, buf);
    }
    close(fd);

    return 0;
}