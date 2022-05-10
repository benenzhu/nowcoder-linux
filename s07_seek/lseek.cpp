/*
#c.
        #include <stdio.h>
        int fseek(FILE *stream, long offset, int whence);
#linux.
        #include <sys/types.h>
        #include <unistd.h>
        off_t lseek(int fd, off_t offset, int whence);
            args:
                - fd: 
                - offset:
                - whence: 
                    SEEK_SET
                    SEEK_END 
                    SEEK_CUR 从当前位置
            返回值：
                返回文件指针的位置
    作用 
        1.移动文件指针
        lseek(fd, 0, SEEK_SET);
        
        2.获取当前文件指针的位置 
        lseek(fd, 0, SEEK_CUR);
        
        3.获取文件的长度
        lseek(fd, 0, SEEK_END);
        
        4.拓展文件的长度 用来创建一定长度的文件。非常的快
        lseek(fd, 100, SEEK_END);
        write(fd, " ", 1);
*/

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
int main() {
    int fd = open("hello.txt", O_RDWR);
    if (fd == -1) {
        perror("open error");
        return -1;
    }

    int res = lseek(fd, 100, SEEK_END);
    if (res == -1) {
        perror("open error");
        return -1;
    }

    // 写入一个空数据
    write(fd, " ", 1);
    close(fd);
    return 0;
}
