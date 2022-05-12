/*
    #include <sys/stat.h>
    #include <sys/types.h>

    int mkdir(const char *pathname, mode_t mode);
        名称和mode
*/

#include "stdio.h"
#include <sys/stat.h>
#include <sys/types.h>
int main() {
    int ret = mkdir("aaa", 0777);
    return 0;
}