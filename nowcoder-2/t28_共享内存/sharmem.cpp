/*

    int shmget(key_t key, size_t size, int shmflg);
        - 创建一个新的内存共享段，或者获取一个已有的
            初始化为 0  
        - @key： 16进制 非0
        - @size: 大小 分页大小
        - @flag: 属性
            - 访问权限
            - 附加属性  
                创建 IPC_CREAT
                判断 IPC_EXCL           
                权限 0664
        - @ret: -1 / > 后面操作都是这个值 
    void *shmat(int shmid, const void *shmaddr, int shmflg);
        - 和当前的进程进行关联
        - @shmid: id 返回值
        - @shmaddr: NULL 自动
        - @flag: 同上
                SHM_EXEC
                读 ： SHM_RDONLY
                读写 ： 0 
        - @ret: 
            成功： 首地址
            失败： (void *) -1 
    int shmdt(const void *shmaddr);
        - 接触当前的关联
        - @shmaddr
        - @ret: 0 / -1
    int shmctl(int shmid, int cmd, struct shmid_ds *buf);
        - 控制函数 : 删除共享内存， 删除才会消失, 创建的被销毁了 对 共享内存没有任何影响
        - @shmid: 
        - @cmd: 
            IPC_STAT : 获取当前的状态 进行操作
            IPC_SET : 设置状态
            IPC_RMID : 标记需要销毁
        - @buf 设置或者获取传出么？ 
            - IPC_STAT 传出
            - IPC_SET 设置
            - IPC_RMID NULL
    key_t ftok(const char *pathname, int proj_id);
        - 根据指定的路径和 int 值 生成一个 创建时候的key 
        - @path: 一定需要存在
        - @proj_id: 使用1个字节
            0 - 255 一般指定一个字符
        









*/
#include <sys/ipc.h>
#include <sys/shm.h>
// 创建 获取 解除
int main() {
}
