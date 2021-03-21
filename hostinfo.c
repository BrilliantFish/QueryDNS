#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv){
    struct in_addr addr;	//IP地址结构
    struct hostent *host;	//DNS主机条目结构
    char **p = NULL;

    if(argc != 2){
        fprintf(stderr, "usage:%s <域名或者IP地址(点分十进制)>", argv[0]);
        exit(1);
    }
    
    //判断是否是IP地址
    if(inet_aton(argv[1], &addr) == 1){	
        host = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    }
    else{
        host = gethostbyname(argv[1]);
    }

    printf("名称: %s\n", host->h_name);
    for(p = host->h_aliases; *p != NULL; p++){
        printf("别名: %s\n", *p);
    }

    for(p = host->h_addr_list; *p != NULL; p++){
        addr.s_addr = *((unsigned int*)*p);
        printf("地址: %s\n", inet_ntoa(addr));
    }

    exit(0);
}
