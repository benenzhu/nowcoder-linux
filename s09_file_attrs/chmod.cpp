/*
    #include <sys/stat.h>
    int chmod(const char *path, mode_t mode);
        参数： 
            path：
            mode: 8进制数
*/

#include <stdio.h>
#include <sys/stat.h>
int main() {
    int ret = chmod("a.txt", 0664);
    if (ret == -1) {
        perror("error change mod");
        return -1;
    }
    puts("ok have file");
    return 0;
}