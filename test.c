#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "network_debug.h"

int main(int argc, char *argv[]){
    char* node;
    char*port_no="11234";
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *rp; /*loop variable*/
    int getaddrinfo_return;
    
    
    if(argc!=2){
        fprintf(stderr, "usage: %s [hostname]\nexample: %s localhost\n",argv[0],argv[0]);
        return -1;
    }

    //node=argv[1];
    print_getaddrinfo(&hints);
    memset(&hints, 0, sizeof(hints));
    if((getaddrinfo_return=getaddrinfo(node,port_no,&hints,&res))!=0){
        fprintf(stderr,"Error: getaddrinfo: %d:%s\n",getaddrinfo_return,gai_strerror(getaddrinfo_return));
        return -2;
    }

    for(rp=res;rp!=NULL;rp=rp->ai_next){
        print_getaddrinfo(rp);
    }
    freeaddrinfo(res);
    return 0;

}