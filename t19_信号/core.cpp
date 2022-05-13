#include <cstring>
#include <stdio.h>
/*
(gdb) core-file core.43960 
    调试时候可以查看错误的信息
ulimit -c 10000 设置生成的core的limit大小
*/
int main() {

    char *buf;
    strcpy(buf, "const char *__restrict src");
    return 0;
}
