/*
    #include <stdio.h>

    int rename(const char *oldpath, const char *newpath);

*/

#include "stdio.h"
#include <sys/stat.h>
#include <sys/types.h>
int main() {
    int ret = rename("aaa", "bbb");
    if (ret == -1) {
        perror("rename");
    }
    return 0;
}