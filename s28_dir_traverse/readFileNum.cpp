/*
    // 打开一个目录
    #include <dirent.h>
    #include <sys/types.h>
    DIR *opendir(const char *name);
        name 名称 
        return 
            DIR 的结构体 / 目录流信息
            错误返回 NULL
    
    // 读取目录中的数据
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
        name 
        return


    #include <dirent.h>
    #include <sys/types.h>
    int closedir(DIR *dirp);
*/

#include <cstddef>
#include <cstdio>
#include <dirent.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <vector>
using namespace std;
// 可能有bug 等下看一下
// 读取某个目录下所有文件的个数和东西
// tree

int getFileNum(const char *);
int main(int argc, char **argv) {

    if (argc < 2) {
        printf("%s path\n", argv[0]);
        return -1;
    }

    // DIR *dir = opendir(argv[1]);
    // struct dirent *name;
    // while ((name = readdir(dir))) {
    //     puts(name->d_name);
    // }
    printf("%d\n", getFileNum(argv[1]));
    return 0;
}

int getFileNum(const char *path) {
    // 1. 打开目录
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("open dir fail");
        return 0;
    }

    struct dirent *ptr = readdir(dir);
    int total = 0;
    while ((ptr = readdir(dir)) != NULL) {
        char *dname = ptr->d_name;

        if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }

        // 判断是否是普通文件
        if (ptr->d_type == DT_DIR) {
            char newPath[256];
            sprintf(newPath, "%s/%s", path, dname);
            total += getFileNum(newPath);

        } else if (ptr->d_type == DT_REG) {
            total++;
        }
    }
    return total;
}