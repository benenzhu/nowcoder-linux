// 模拟实现 ls -l 函数
// -rwxr-xr-x 1 z z 20976 May 10 20:52 a.out
#include "pwd.h"
#include <cstdio>
#include <grp.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

    // 给出提示
    if (argc < 2) {
        printf("%s filename\n", argv[0]);
        return -1;
    }

    // 通过 stat 获取信息
    struct stat st;
    int ret = stat(argv[1], &st);
    if (ret == -1) {
        perror("stat");
        return -1;
    }

    // 获取文件类型和文件权限
    char perms[11] = {0};
    switch (st.st_mode & S_IFMT) {
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFREG:
            perms[0] = '-';
            break;
        case S_IFSOCK:
            perms[0] = 's';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFIFO:
            perms[0] = 't';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        default:
            perms[0] = '?';
    }

    // 判断文件的权限

    // 文件所有者
    perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';

    perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';

    perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

    // 硬链接数
    int linkNum = st.st_nlink;

    // 所有者名称
    char *fileUsr = getpwuid(st.st_uid)->pw_name;
    // 文件所在组
    char *fileGrp = getgrgid(st.st_gid)->gr_name;

    auto filesize = st.st_size;

    char *time = ctime(&st.st_mtime);

    char mtime[1024] = {0};
    strncpy(mtime, time, strlen(time) - 1);
    puts("change the time");
    char bufs[1024];
    sprintf(bufs, "%s %d %s %s %ld %s %s", perms, linkNum, fileUsr, fileGrp, filesize, mtime, argv[1]);
    puts(bufs);
    return 0;
}