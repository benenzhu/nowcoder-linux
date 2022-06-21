#include <stdio.h>

#define PI 3.14

int main(){
    // 测试.i 文件
    int sum = PI + 10;
    puts("hello world");
    return 0; 
}


// gcc test.c -E -o test.i
// gcc test.i -S -o test.s 汇编
// gcc test.s -c -o test.o 编译 还没有进行链接
// gcc test.o -o test.out 这个链接命令是啥呢？