#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("hello\n"); // 只有在遇到换行的时候才会去刷新
    printf("world");

    // exit(0);
    _exit(0);

    puts("exit");
    return 0;
}
