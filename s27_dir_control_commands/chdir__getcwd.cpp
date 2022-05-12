/*
    #include <unistd.h>

    int chdir(const char *path);
        作用：修改进程的工作目录
        path: 工作目录 
    int fchdir(int fd);


    #include <unistd.h>

    char *getcwd(char *buf, size_t size);
        作用： 获取当前的工作目录
        参数：
            buf 
            size 
    char *getwd(char *buf);
    char *get_current_dir_name(void);
*/
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {

    //获取当前的工作目录
    char buf[128];
    getcwd(buf, sizeof(buf));

    printf("当前的工作目录是: %s\n", buf);

    int ret = chdir("..");
    if (ret == -1) {
        perror("chdir 失败");
        return -1;
    }

    getcwd(buf, sizeof(buf));

    printf("当前的工作目录是: %s\n", buf);

    // 创建一个新的文件
    open("chdir.txt", O_CREAT | O_RDWR, 0664);

    return 0;
}
