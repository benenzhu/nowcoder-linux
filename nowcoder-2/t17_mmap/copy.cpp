// 使用mmap进行copy文件
/*
    1. mmap旧的文件
    2. mmap新的文件 同样的大小
    3. 拷贝内存
    4. 关闭两个mmap

*/
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {

    int old_fd = open("test.txt", O_RDONLY);
    if (old_fd == -1) {
        perror("open error");
    }
    int len = lseek(old_fd, 0, SEEK_END);
    auto old_addr = mmap(NULL, len, PROT_READ, MAP_SHARED, old_fd, 0);
    if (old_addr == MAP_FAILED) {
        perror("map failed");
        exit(0);
    }

    int new_fd = open("new.txt", O_RDWR | O_CREAT, 0664);
    if (new_fd == -1) {
        perror("open error");
    }
    int new_len = lseek(new_fd, len, SEEK_CUR);
    write(new_fd, " ", 1);

    auto new_addr = mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, new_fd, 0);
    if (new_addr == MAP_FAILED) {
        perror("map failed");
        exit(0);
    }

    memcpy(new_addr, old_addr, len);

    munmap(new_addr, len);
    munmap(old_addr, len);
    close(new_fd);
    close(old_fd);

    return 0;
}
