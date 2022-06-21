#include <cstdio>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {

    // 1. 创建
    int shmid = shmget(100, 4096, IPC_CREAT | 0664);
    printf("shmid : %d\n", shmid);

    // 2. 关联
    void *ptr = shmat(shmid, nullptr, 0);

    // 3. 写数据
    char str[] = "hello memory";
    memcpy(ptr, str, strlen(str));

    printf("按任意键继续\n");
    getchar();
    // 4. 接触关联
    shmdt(ptr);

    // 5. 删除
    shmctl(shmid, IPC_RMID, nullptr);

    return 0;
}