/*
SYNOPSIS
        #include <unistd.h>

        ssize_t read(int fd, void *buf, size_t count);
            args：
                - fd：文件描述符， open得到的，可以操纵文件
                - buf: 缓冲区 需要读取数据存放的地方 数组的地址
                - count: 指定的数据的大小
            返回值：
                - 成功：
                    >0: 返回实际的字节数
                    =0：文件已经被读完了
                - 失败：
                    -1：并设置 errno
SYNOPSIS
        #include <unistd.h>

        ssize_t write(int fd, const void *buf, size_t count);
            args:
                - fd:
                - buf:
                - count:
            return:
                成功：返回实际写入的字节数
                失败：返回 -1
*/

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
int main() {
    // 1. open infile
    int src_fd = open("a.txt", O_RDONLY);
    // 2. create && opepn out.txt
    int dst_fd = open("b.txt", O_CREAT | O_WRONLY, 0664);
    if (src_fd == -1 || dst_fd == -1) {
        perror("have error:");
        return -1;
    }
    // 3. read & writes... 读写这里注意一下
    char buf[110];
    int len;
    while ((len = read(src_fd, buf, sizeof(buf))) > 0) {
        write(dst_fd, buf, len);
    }
    // 4. close the files
    close(src_fd);
    close(dst_fd);
    return 0;
}
