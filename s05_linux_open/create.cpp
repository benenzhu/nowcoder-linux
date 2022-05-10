#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    /*
        -flags 可选项：O_CREAT 文件不存在，创建新文件
        -mode: 最终的mode
            mode & ~umask
            0777 ->

            umask 是多少呢？ 默认 0022
    */
    int fd = open("create.txt", O_RDWR | O_CREAT, 0777);
    // 每一个代表着是 32 位里面的一个标记
    if (fd == -1) {
        perror("open error");
    }
    close(fd);
    return 0;
}