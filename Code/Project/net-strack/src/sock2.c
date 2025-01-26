#include "sock2.h"

#define MAX_FDS 1024

static int fd = 0;
static Sock2Fd sock2fds[MAX_FDS];

int socket2(int domain, int type, int protocol) {
    if (fd >= MAX_FDS || fd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fds[fd++];
    sock2fd->domain = domain;
    sock2fd->type = type;
    sock2fd->protocol = protocol;
    sock2fd->fd = fd;
    sock2fd->state = CLOSED;

    sock2fd->alldevs = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *device = device_find(sock2fd->alldevs, "\\Device\\NPF_{134C479A-F628-4EB6-81C1-06406359BCDC}");
    if (!device) LOG_ERROR("device_find", "The device does not exist!");

    pcap_t *handle = pcap_open_live(device->name, 65535, 0, 1000, errbuf);
    if (!handle) {
        pcap_freealldevs(sock2fd->alldevs);
        return 1;
    }
    sock2fd->handle = handle;
    return fd;
}

int bind2(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    if (sockfd >= MAX_FDS || sockfd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fd[sockfd - 1];
    memcpy(&sock2fd->addr, addr, addrlen);
    return 0;
}

int listen2(int sockfd, int backlog) {
    if (sockfd >= MAX_FDS || sockfd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fds[sockfd - 1];
    sock2fd->backlog = backlog;
    sock2fd->state = LISTEN;
    return 0;
}

int accept2(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    if (sockfd >= MAX_FDS || sockfd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fds[sockfd - 1];
    if (sock2fd->state != LISTEN) return 2;

    int ret = pcap_loop(sock2fd->handle, -1, device_handle, NULL);
    if (ret < 0) return ret;

    sock2fd ->state = SYN_RECEIVED;
    ret = pcap_loop(sock2fd->handle, -1, device_handler, NULL);
    if (ret < 0) return ret;

    sock2fd->state = ESTABLISHED;
    return 0;
}

int recv2(int sockfd, void *buf, size_t len, int flags) {
    if (sockfd >= MAX_FDS || sockfd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fds[sockfd -1];

    sock2fd->state = CLOSE_WAIT;
    sock2fd->state = LAST_ACK;
    sock2fd->state = CLOSED;
    return 0;
}

int close2(int sockfd) {
    if (sockfd >= MAX_FDS || sockfd < 0) return 1;

    Sock2Fd *sock2fd = &sock2fds[sockfd - 1];

    sock2fd->state = FIN_WAIT1;
    int ret = pcap_loop(sock2fd->handle, -1, device_handler, NULL);
    if (ret < 0) return ret;

    sock2fd->state = FIN_WAIT2;
    ret = pcap_loop(sock2fd->handle, -1, device_handler, NULL);
    if (ret < 0) return ret;

    sock2fd->state = TIME_WAIT;
    sock2fd->state = CLOSED;
    pcap_close()
}