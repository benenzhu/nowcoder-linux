/*
    #include <unistd.h>

    int access(const char *pathname, int mode);
        作用：判断某个文件是否有某个权限 / 是否存在
        参数：
            - pathanme:
            - mode:
                R_OK:
                W_OK:
                X_OK:
                F_OK: 文件是否存在
        - return 
            0 / -1
*/

#include "stdio.h"
#include <unistd.h>
int main() {
    int ret = access("a.txt", F_OK);
    if (ret == -1) {
        perror("access");
        return -1;
    }
    puts("文件存在");

    return 0;
}