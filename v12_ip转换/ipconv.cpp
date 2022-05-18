/*
NAME
       inet_aton,  inet_addr,  inet_network,  inet_ntoa,  inet_makeaddr,  inet_lnaof,  inet_netof - Internet
       address manipulation routines

SYNOPSIS
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <arpa/inet.h>

    --------------------------------
       int inet_aton(const char *cp, struct in_addr *inp);
            - 字符串 到 ip 地址

       char *inet_ntoa(struct in_addr in);

       in_addr_t inet_addr(const char *cp); // 旧的 不可重用
    --------------------------------

       in_addr_t inet_network(const char *cp);

       struct in_addr inet_makeaddr(int net, int host);

       in_addr_t inet_lnaof(struct in_addr in);

       in_addr_t inet_netof(struct in_addr in);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       inet_aton(), inet_ntoa(): _BSD_SOURCE || _SVID_SOURCE
##############################################
// 推荐用底下这两个
NAME
       inet_pton - convert IPv4 and IPv6 addresses from text to binary form
        - p: 点分十进制的字符串
        - n: 网络字节序的整数
SYNOPSIS
       #include <arpa/inet.h>

       int inet_pton(int af, const char *src, void *dst);
            -af: 地址族，  AF_INET AF_INET6
            -src: 需要转换的ip地址
            -dst: 转换后的结果
##############################################
NAME
       inet_ntop - convert IPv4 and IPv6 addresses from binary to text form

SYNOPSIS
       #include <arpa/inet.h>

       const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);
            - af 可以指定
            - size 指定 dst 的 buffer 的 size
            - return 和 dst 是同一个东西

*/
#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>


int main(){
    // 创建一个ip字符串
    char buf[] = "192.168.1.4";
    unsigned int num; 
    int ret = inet_pton(AF_INET, buf, &num);
    unsigned char * p = (unsigned char *)&num;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));


    // 重新转回去  
    char buf2[16] = {0};
    const char* str_ret =  inet_ntop(AF_INET, &num, buf2, sizeof(buf2));
    puts(buf2);
    puts(str_ret);
    printf("%d", buf2 == str_ret);



    return 0; 
}