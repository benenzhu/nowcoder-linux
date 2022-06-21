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

    int ret = access("fifo2", F_OK);
    if (ret == -1) {
        puts("fifo2 不存在, 创建");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }
    // 2.以只写的方式打开管道 fifo1
    int pipe1 = open("fifo1", O_RDONLY);
    int pipe2 = open("fifo2", O_WRONLY);

    while (1) {
        char buf[1024] = {0};
        int n = read(pipe1, buf, sizeof(buf));

        printf("ChatB: Recv: %s", buf);
        char buf2[1024] = "hello world\n";

        write(pipe2, buf2, strlen(buf2));
        sleep(1);
    }
    close(pipe1);
    close(pipe2);

    return 0;
}