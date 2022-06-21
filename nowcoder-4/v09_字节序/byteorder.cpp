#include <cstdio>

void judge() {
    union {
        short value;
        char bytes[sizeof(short)];
    } test;

    test.value = 0x0102;

    if ((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
        puts("大端字节序");
    } else if ((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
        puts("小端字节序");
    } else {
        puts("错误字节序");
    }
}

int main() {
    unsigned int a = 0x12345678;
    char *addr = (char *) &a;

    for (int i = 0; i < 4; i++) {
        printf("%x:", *(addr + i)); // %x 打印 16进制
    }
    puts("");
    judge();
}