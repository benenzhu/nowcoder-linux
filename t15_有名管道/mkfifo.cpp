#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
    /*
    int mkfifo(const char *path, __mode_t mode)
        @path
        @mode 权限 和 open mode是一样的 umask
        @return 0 / -1 error 
    */
    // 创建每一个 fifo
    int ret = mkfifo("fifo1", 0664);
    if (ret == -1) {
        perror("mkfifo");
        exit(-1);
    }

    return 0;
}