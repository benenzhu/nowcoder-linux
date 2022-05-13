/*


*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
    // 1. 管道文件是否存在

    int ret = access("fifo1", F_OK);
    if (ret == -1) {
        puts("fifo1 不存在, 创建");
        ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }
    // 2.以只写的方式打开管道 fifo1
    int pipe1 = open("fifo1", O_WRONLY);
    // todo 错误
    int pipe2 = open("fifo2", O_RDONLY);
    // todo 错误

    while (1) {
        char buf[128];

        bzero(buf, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        write(pipe1, buf, strlen(buf));

        bzero(buf, sizeof(buf));
        int ret = read(pipe2, buf, sizeof(buf));
        if (ret <= 0) {
            perror("read");
            break;
        }
        printf("ChatA: Recv: %s", buf);
    }

    close(pipe1);
    close(pipe2);
    return 0;
}