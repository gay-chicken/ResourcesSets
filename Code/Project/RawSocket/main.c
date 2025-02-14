#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

// 伪头部结构，用于计算TCP校验和
struct pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};

// TCP头部结构
struct tcp_header {
    u_int16_t th_sport;
    u_int16_t th_dport;
    u_int32_t th_seq;
    u_int32_t th_ack;
    u_int8_t th_x2:4;
    u_int8_t th_off:4;
    u_int8_t th_flags;
    u_int16_t th_win;
    u_int16_t th_sum;
    u_int16_t th_urp;
};

// IP头部结构
struct ip_header {
    u_int8_t ip_hl:4;
    u_int8_t ip_v:4;
    u_int8_t ip_tos;
    u_int16_t ip_len;
    u_int16_t ip_id;
    u_int16_t ip_off;
    u_int8_t ip_ttl;
    u_int8_t ip_p;
    u_int16_t ip_sum;
    struct in_addr ip_src;
    struct in_addr ip_dst;
};

// 校验和计算函数
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    while (len > 1) {
        sum += *buf++;
        len -= 2;
    }

    if (len == 1) {
        sum += *(unsigned char *)buf;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    int sock;
    struct sockaddr_in dest;
    struct ip_header ip;
    struct tcp_header tcp;
    struct pseudo_header psh;

    // 创建原始套接字
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    dest.sin_family = AF_INET;
    dest.sin_port = htons(80);  // 目标端口（HTTP）
    dest.sin_addr.s_addr = inet_addr("192.168.1.1");  // 目标IP地址

    // 填充IP头部
    memset(&ip, 0, sizeof(ip));
    ip.ip_hl = 5;
    ip.ip_v = 4;
    ip.ip_tos = 0;
    ip.ip_len = sizeof(struct ip_header) + sizeof(struct tcp_header);
    ip.ip_id = htonl(54321);  // 唯一的ID
    ip.ip_off = 0;
    ip.ip_ttl = 255;
    ip.ip_p = IPPROTO_TCP;
    ip.ip_sum = 0;
    ip.ip_src.s_addr = inet_addr("192.168.1.100");  // 本地IP地址
    ip.ip_dst = dest.sin_addr;

    ip.ip_sum = checksum(&ip, sizeof(struct ip_header));

    // 填充TCP头部
    memset(&tcp, 0, sizeof(tcp));
    tcp.th_sport = htons(12345);  // 源端口
    tcp.th_dport = htons(80);  // 目标端口
    tcp.th_seq = 0;  // 序列号
    tcp.th_ack = 0;  // ACK号
    tcp.th_x2 = 0;
    tcp.th_off = 5;
    tcp.th_flags = TH_SYN;  // 设置SYN标志
    tcp.th_win = htons(5840);  // 窗口大小
    tcp.th_sum = 0;  // 校验和初始化
    tcp.th_urp = 0;

    // 伪头部，用于计算TCP校验和
    psh.source_address = inet_addr("192.168.1.100");  // 源地址
    psh.dest_address = dest.sin_addr.s_addr;  // 目标地址
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcp_header));

    int psize = sizeof(struct pseudo_header) + sizeof(struct tcp_header);
    char *pseudogram = malloc(psize);

    memcpy(pseudogram, (char *)&psh, sizeof(struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header), (char *)&tcp, sizeof(struct tcp_header));

    tcp.th_sum = checksum((unsigned short *)pseudogram, psize);

    // 发送SYN包
    char packet[4096];
    memcpy(packet, &ip, sizeof(struct ip_header));
    memcpy(packet + sizeof(struct ip_header), &tcp, sizeof(struct tcp_header));

    if (sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("Send failed");
    }

    printf("SYN包已发送\n");

    // 监听SYN-ACK包并解析
    struct sockaddr_in recv_addr;
    socklen_t addr_len = sizeof(recv_addr);
    unsigned char buffer[65536];

    while (1) {
        int data_size = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&recv_addr, &addr_len);
        if (data_size < 0) {
            perror("Error receiving packet");
            continue;
        }

        // 解析包并检查是否是SYN-ACK
        struct ip_header *ip_header = (struct ip_header *)buffer;
        struct tcp_header *tcp_header = (struct tcp_header *)(buffer + (ip_header->ip_hl * 4));

        if (tcp_header->th_flags == (TH_SYN | TH_ACK)) {
            printf("收到SYN-ACK包\n");

            // 发送ACK包
            tcp.th_seq = htonl(1);  // 确认号
            tcp.th_ack = ntohl(tcp_header->th_seq) + 1;  // ACK号
            tcp.th_flags = TH_ACK;  // 设置ACK标志
            tcp.th_sum = 0;

            // 计算校验和
            psh.tcp_length = htons(sizeof(struct tcp_header));
            pseudogram = malloc(sizeof(struct pseudo_header) + sizeof(struct tcp_header));
            memcpy(pseudogram, (char *)&psh, sizeof(struct pseudo_header));
            memcpy(pseudogram + sizeof(struct pseudo_header), (char *)&tcp, sizeof(struct tcp_header));
            tcp.th_sum = checksum((unsigned short *)pseudogram, sizeof(struct pseudo_header) + sizeof(struct tcp_header));

            // 发送ACK包
            memset(packet, 0, sizeof(packet));
            memcpy(packet, &ip, sizeof(struct ip_header));
            memcpy(packet + sizeof(struct ip_header), &tcp, sizeof(struct tcp_header));

            if (sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
                perror("ACK Send failed");
            }
            printf("发送ACK包，完成三次握手\n");
            break;  // 完成三次握手，退出循环
        }
    }

    close(sock);
    return 0;
}
