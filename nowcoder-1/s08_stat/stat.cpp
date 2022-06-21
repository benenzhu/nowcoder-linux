/*
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>

    int stat(const char *path, struct stat *buf);
        作用： 返回一个文件的信息 返回在buf里面
        参数：
            - path 文件路径
            - buf 结构体变量，传出参数
        返回值：
            成功：0
            失败：-1
    int lstat(const char *path, struct stat *buf);
        区别: 获取软链接文件的信息
*/

#include "unistd.h"
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
int main() {

    struct stat buf;

    int ret = stat("a.txt", &buf);

    if (ret == -1) {
        perror("error stat");
        return -1;
    }

    printf("size %ld\n", buf.st_size);

    return 0;
}