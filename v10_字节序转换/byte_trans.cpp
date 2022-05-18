/*
NAME
       htonl, htons, ntohl, ntohs - convert values between host and network byte order

SYNOPSIS
       #include <arpa/inet.h>

       uint16_t ntohs(uint16_t netshort);
       uint16_t htons(uint16_t hostshort); 

       uint32_t ntohl(uint32_t netlong);
       uint32_t htonl(uint32_t hostlong);
       
       // 网络通信时，需要将主机转换成网络，另外一端获取到后需要转换成 host 字节序
       - h host 主机
       - n network 网络
       - s short 短 2byte 一般是转换端口的
       - l long 长 4byte 一般是转换ip的

*/

#include<arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
int main(){
    // htons 转换端口
    unsigned short a = 0x0102;
    unsigned short b = htons(a);
    printf("a:%0x, b:%0x\n", a, b);

    // htonl 转换 ip
    unsigned char buf[4] = {192, 168,1,100}; // 这样转换是对么？
    unsigned int num = *(int *)buf;
    unsigned int out = htonl(num);

    unsigned char *p = (unsigned char *)&out;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2),*(p+3)) ;

    // ======================= 
    
    return 0;
}