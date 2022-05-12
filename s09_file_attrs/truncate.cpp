/*

    #include <sys/types.h>
    #include <unistd.h>

    int truncate(const char *path, off_t length);
        作用： 
            - length 最终文件需要变成的大小
            

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int ret = truncate("b.txt", 5);
    if (ret == -1) {
        perror("truncate 错误");
        return -1;
    }
    puts("ok");
    return 0;
}