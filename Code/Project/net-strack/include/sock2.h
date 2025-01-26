#ifndef SOCK2_H
#define SOCK2_H

#include "pcap.h"

// domain
#define AF_INET 1

// type
#define SOCK_STREAM 1
#define SOCK_DGRAM 2

// protocol
#define IPPPROTO_TCP 6
#define IPPPROTO_UDP 17

typedef enum {
    CLOSED,
    LISTEN,
    SYN_SENT,
    SYN_RECEIVED,
    ESTABLISHED,
    FIN_WAIT1,
    FIN_WAIT2,
    TIME_WAIT,
    LAST_ACK,
    CLOSE_WAIT,
} State;

typedef struct {
    int domain;
    int type;
    int protocol;
    int fd;
    State state;
    union {
        struct sockaddr;
        struct sockaddr_in;
    } addr;
    int backlog;
    pcap_if_t *alldevs;
    pcap_t *handle;
} Sock2Fd;

int socket2(int domain, int type, int protocol);
int bind2(int sockfd, struct sockaddr *addr, socklen_t addrlen);
int listen2(int sockfd, int backlog);

int accept2(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int connect2(int sockfd, struct sockaddr *addr, socklen_t aaddrlen);
int send2(int sockfd, const void *buf, size_t len, int flags);
int recv2(int sockfd, void *buf, size_t len, int flags);

int close2(int sockfd);
#endif // end of SOCK2_H