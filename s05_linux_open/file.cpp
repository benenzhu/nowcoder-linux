/*
    #include <fcntl.h>
    #include <sys/stat.h>
   #include <sys/types.h>

    // 打开一个已经存在的文件
    int open(const char *pathname, int flags);
        - pathname 要打开的文件路径
        - flags
            访问权限 O_REONLY O_WRONLY ORDWR 这三个设置是互斥的
        - 返回 文件描述符 -1 如果出错 errno 将被设置成合适的值
    

    errno: 属于linux系统库的全局变量， 记录的最近的错误号
        如何打印
    perror .. 可以打印错误
        打印error 对应的错误描述
    #include <stdio.h>
    void perror(const char *s);
        s参数， 用户在error里面追加的值
        
    

    // 创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);

    int creat(const char *pathname, mode_t mode);
*/

#include "sys/stat.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    int fd = open("a.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open Error");
    }

    // 读写操作

    // 关闭这个文件；
    close(fd);

    return 0;
}