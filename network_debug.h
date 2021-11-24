#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void print_socket_domain(const int a){
    if(a==AF_INET){
        printf("AF_INET: IPv4 Internet protocols / man 7 ip\n");
    }else if(a==AF_INET6){
        printf("AF_INET6: IPv6 Internet protocols / man 7 ipv6\n");
    }else if(a==AF_UNSPEC){
        printf("AF_UNSPEC\n");
    }else if(a==AF_UNIX){
        printf("AF_UNIX: Local communication / man 7 unix\n");
    }else if(a==AF_LOCAL){
        printf("AF_LOCAL: Local communication / man 7 unix\n");
    }else if(a==AF_IPX){
        printf("AF_IPX: IPX - Novell protocols\n");
    }else if(a==AF_NETLINK){
        printf("AF_NETLINK: Kernel user interface device / man 7 netlink\n");
    }else if(a==AF_X25){
        printf("AF_X25: ITU-T X.25 / ISO-8208 protocol / man 7 x25\n");
    }else if(a==AF_AX25){
        printf("AF_AX25: Amateur radio AX.25 protocol\n");
    }else if(a==AF_ATMPVC){
        printf("AF_ATMPVC: Access to raw ATM PVCs\n");
    }else if(a==AF_APPLETALK){
        printf("AF_APPLETALK: AppleTalk / man 7 ddp\n");
    }else if(a==AF_PACKET){
        printf("AF_PACKET: Low level packet interface / man 7 packet\n");
    }else if(a==AF_ALG){
        printf("AF_ALG: Interface to kernel crypto API\n");
    }else{
        printf("(invalid?) %d\n",a);
    }
    return;
}

void print_socket_type(const int type){
    int base_type=type;
    if(type==0){
        printf("0\n");
        return;
    }
    if((base_type&SOCK_NONBLOCK)==SOCK_NONBLOCK){
        base_type-=SOCK_NONBLOCK;
    }
    if((base_type&SOCK_CLOEXEC)==SOCK_CLOEXEC){
        base_type-=SOCK_CLOEXEC;
    }
    switch(base_type){
        case SOCK_STREAM:
        printf("SOCK_STREAM");
        break;
        case SOCK_DGRAM:
        printf("SOCK_DGRAM");
        break;
        case SOCK_SEQPACKET:
        printf("SOCK_SEQPACKET");
        break;
        case SOCK_RAW:
        printf("SOCK_RAW");
        break;
        case SOCK_RDM:
        printf("SOCK_RDM");
        break;
        case SOCK_PACKET:
        printf("SOCK_PACKET");
        break;
        default:
        printf("(unknown) %d",base_type);
    }
    if((type&SOCK_NONBLOCK)==SOCK_NONBLOCK){
        printf("|SOCK_NONBLOCK");
    }
    if((type&SOCK_CLOEXEC)==SOCK_CLOEXEC){
        printf("|SOCK_CLOEXEC");
    }
    printf("\n");
    return;
}

void print_sockaddr_in(const struct sockaddr_in *a){
    char addr_buf[64];
    if(a==NULL){
        printf("sockaddr_in: NULL\n");
        return;
    }
    if(a->sin_family!=AF_INET){
        printf("sin_family: ");
        print_socket_domain(a->sin_family);
        return;
    }
    printf("sin_family: AF_INET\n");
    inet_ntop(AF_INET, &a->sin_addr, addr_buf, sizeof(addr_buf));
    printf("sin_addr: %s\n", addr_buf);
    printf("sin_port: %d\n",ntohs(a->sin_port));
}

void print_sockaddr_in6(const struct sockaddr_in6 *a){
    char addr_buf[64];
    if(a==NULL){
        printf("sockaddr_in6: NULL\n");
        return;
    }
    if(a->sin6_family!=AF_INET6){
        printf("sin6_family: ");
        print_socket_domain(a->sin6_family);
        return;
    }
    printf("sin6_family: AF_INET6\n");
    inet_ntop(AF_INET6, &a->sin6_addr, addr_buf, sizeof(addr_buf));
    printf("sin6_addr: %s\n", addr_buf);
    printf("sin6_flowinfo: %d\n",a->sin6_flowinfo);
    printf("sin6_port: %d\n",ntohl(a->sin6_port));
}

void print_getaddrinfo(const struct addrinfo *rp){
    if(rp==NULL){
        printf("NULL\n\n");
        return;
    }
    printf("ai_flags: %d\n",rp->ai_flags);
    printf("ai_family: ");
    print_socket_domain(rp->ai_family);
    printf("ai_socktype: ");
    print_socket_type(rp->ai_socktype);
    printf("ai_protocol: %d\n", rp->ai_protocol);
    printf("ai_addrlen: %d\n", (int) rp->ai_addrlen);
    if(rp->ai_family == AF_INET) {
        print_sockaddr_in((struct sockaddr_in *)rp->ai_addr);
    } else if(rp->ai_family == AF_INET6) {
        print_sockaddr_in6((struct sockaddr_in6 *)rp->ai_addr);
    }
    printf("ai_canonname: %s\n\n", rp->ai_canonname?rp->ai_canonname:"NULL");

}
