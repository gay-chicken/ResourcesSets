#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"
#include "log.h"

EthII_Hdr *eth_ii_parse(const unsigned char *data) {
    EthII_Hdr *eth_ii = malloc(sizeof(EthII_Hdr));
    if (!eth_ii) LOG_ERROR("eth_ii_parse", "Allocation memory failed!");

    memcpy(eth_ii, data, sizeof(EthII_Hdr));
    eth_ii->type = ntohs(eth_ii->type);
    return eth_ii;
}

void eth_ii_print(const EthII_Hdr *eth_ii) {
    if (eth_ii == NULL) return;

    switch(eth_ii->type) {
        case ETH_II_TYPE_IPV4: printf("IPv4"); break;
        case ETH_II_TYPE_IPV6: printf("IPv6"); break;
        case ETH_II_TYPE_ARP: printf("ARP");  break;
        default: printf("Unknown");
    }

    printf(":\t%s -> %s\n", mac2str(eth_ii->source_mac), mac2str(eth_ii->target_mac));
}

char *mac2str(const unsigned char *mac) {
    if (mac == NULL) return NULL;

    char *mac_str = malloc(ETH_II_MAC_LEN + 1);
    if (!mac_str) LOG_ERROR("mac2str", "Allocation memory failed!");

    memset(mac_str, 0, ETH_II_MAC_LEN + 1);
    // memcpy(mac_str, mac, ETH_II_MAC_LEN);
    sprintf(mac_str, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return mac_str;
}

char *ip2str(const uint32_t data) {
    char *ip_str = malloc(sizeof(uint32_t) + 1);
    if (!ip_str) LOG_ERROR("ip2str", "Allocation memory failed!");

    memset(ip_str, 0, sizeof(uint32_t) + 1);
    sprintf(ip_str, "%u.%u.%u.%u", (data & 0xff000000) >> 24, (data & 0x00ff0000) >> 16, (data & 0x0000ff00) >> 8, (data & 0x000000ff));
    return ip_str;
}

Arp_Hdr *arp_parse(const unsigned char *data) {
    Arp_Hdr *arp_hdr = malloc(sizeof(Arp_Hdr));
    if (!arp_hdr) LOG_ERROR("arp_parse", "Allocation memory failed!");

    memcpy(arp_hdr, data, sizeof(Arp_Hdr));
    arp_hdr->h_type = ntohs(arp_hdr->h_type);
    arp_hdr->p_type = ntohs(arp_hdr->p_type);
    arp_hdr->oper = ntohs(arp_hdr->oper);
    arp_hdr->spa = ntohl(arp_hdr->spa);
    arp_hdr->tpa = ntohl(arp_hdr->tpa);
    return arp_hdr;
}

void arp_print(const Arp_Hdr *arp) {
    if (!arp) return;

    switch(arp->p_type) {
        case ETH_II_TYPE_IPV4:
            printf("\t\t who has %s, tell %s\n", ip2str(arp->tpa), ip2str(arp->spa));
            break;
        default:
            LOG_ERROR("arp_print", "Unknown protocol type!");
    }
}

int arp_send(pcap_t *handle, char *tpa, uint8_t type) {
    EthII_Hdr eth_ii_hdr = {.type = htons(ETH_II_TYPE_ARP)};
    host_mac(eth_ii_hdr.source_mac);
    memset(eth_ii_hdr.target_mac, 0xFF, ETH_II_MAC_LEN);
    Arp_Hdr arp_hdr = {
        .h_type = htons(1),
        .p_type = htons(ETH_II_TYPE_IPV4),
        .h_len = 6,
        .p_len = 4,
        .oper = htons(1),
        .spa = inet_addr("192.168.31.16"), // TODO: 需要将静态的IP地址转换为动态获取
        .tpa = inet_addr("192.168.31.16")
    };
    host_mac(arp_hdr.sha);
    int p_len = 0;
    if (type == ARP_GRATUITOUS) {
        p_len = 60;
        memset(arp_hdr.tha, 0xFF, ETH_II_MAC_LEN);
    } else if (type == ARP_REQUEST) {
        p_len = sizeof(EthII_Hdr) + sizeof(Arp_Hdr);
        memset(arp_hdr.tha, 0, ETH_II_MAC_LEN);
        arp_hdr.tpa = inet_addr(tpa);
    }

    uint8_t data[p_len];
    memset(data, 0, p_len);
    memcpy(data, &eth_ii_hdr, sizeof(EthII_Hdr));
    memcpy(data + sizeof(EthII_Hdr), &arp_hdr, sizeof(Arp_Hdr));
    if (pcap_sendpacket(handle, data, p_len)) LOG_ERROR("pcap_sendpacket", pcap_geterr(handle));
    else printf("Send successfully.\n");
}

Icmp_Hdr *icmp_hdr;

Ip_Hdr *ip_parse(const unsigned char *data)
{
    Ip_Hdr *ip_hdr = malloc(sizeof(Ip_Hdr));
    if (ip_hdr == NULL) LOG_ERROR("ip_parse", "Allocation memory failed!");
    memcpy(ip_hdr, data, sizeof(Ip_Hdr));
    if (ip_checksum(ip_hdr))  {
        free(ip_hdr);
        LOG_ERROR("ip_checksum", "The verification code fails to be verified.");
    }
    ip_hdr->len = ntohs(ip_hdr->len);
    ip_hdr->identification = ntohs(ip_hdr->identification);
    ip_hdr->ff.v = ntohs(ip_hdr->ff.v);
    ip_hdr->checksum = ntohs(ip_hdr->checksum);
    ip_hdr->src = ntohl(ip_hdr->src);
    ip_hdr->dst = ntohl(ip_hdr->dst);

    if (ip_hdr->protocol == IP_TOP_ICMP) {
        uint16_t hl = ip_hdr->ihl * 4;
        icmp_hdr = icmp_parse(data + hl, ip_hdr->len - hl);
    }
    return ip_hdr;
}

void ip_print(const Ip_Hdr *ip)
{
    printf("\t\tHeader: %u bytes, Total: %u bytes\n", ip->ihl, ip->len);
    printf("\t\tCHK: %#4x\n", ip->checksum);
    printf("\t\tTTL: %u\n", ip->ttl);
    if (ip->protocol == IP_TOP_TCP) {
        printf("\t\tTOP: TCP\n");
    } else if (ip->protocol == IP_TOP_UDP) {
        printf("\t\tTOP: UDP\n");
    } else if (ip->protocol == IP_TOP_ICMP) {
        printf("\t\tTOP: ICMP\n");
    } else {
        LOG_ERROR("ip_print", "Unknown Ip protocol type!");
    }
    printf("\t\tIP: %s -> %s\n", ip2str(ip->src), ip2str(ip->dst));
}

static uint16_t checksum(void *data, int len)
{
    uint32_t sum = 0;
    uint16_t *ptr = data;

    // 遍历数据，按2字节累加
    while(len > 1) {
        sum += *ptr++;
        if (sum > 0xFFFF) {
            sum = (sum & 0xFFFF) + 1; // 进位加一
        }
        len -= 2;
    }

    // 如果长度是奇数，处理最后一个字节
    if (len == 1) {
        uint8_t last_byte = *(uint8_t *)ptr;
        sum += (last_byte << 8); // 高位补齐
        if (sum > 0xFFFF) {
            sum = (sum & 0xFFFF) + 1;
        }
    }

    return ~sum; // 取反，返回校验和
}

int ip_checksum(Ip_Hdr *ip_hdr)
{
    uint16_t recv_checksum = ip_hdr->checksum;
    ip_hdr->checksum = 0;
    if (checksum(ip_hdr, ip_hdr->ihl * 4) == recv_checksum) {
        ip_hdr->checksum = recv_checksum;
        return 0;
    }
    return 1;
}

Icmp_Hdr *icmp_parse(const unsigned char *data, uint16_t len)
{
    Icmp_Hdr *icmp_hdr = malloc(len);
    if (icmp_hdr == NULL) LOG_ERROR("icmp_parse", "Allocation memory failed!");

    memcpy(icmp_hdr, data, len);
    if (icmp_checksum(icmp_hdr, len)) {
        free(icmp_hdr);
        LOG_ERROR("icmp_checksum", "The verification code fails to be verified.");
    }
    return icmp_hdr;
}

int icmp_checksum(Icmp_Hdr *icmp, uint16_t len)
{
    return checksum(icmp, len);
}

void icmp_print(const Icmp_Hdr *icmp)
{
    printf("ICMP Type: ");
    if (icmp->type == 0 && icmp->code == 0) {
        printf("Echo Reply\n");
    } else if (icmp->type == 8 && icmp->code == 0) {
        printf("Echo Request\n");
    } else {
        printf("Unsupport\n");
    }
}

Udp_Hdr *udp_parse(const unsigned char *data, uint16_t len)
{
    Udp_Hdr *udp_hdr = malloc(sizeof(Udp_Hdr));
    if (!udp_hdr) LOG_ERROR("udp_parse", "Allocation memory failed!");

    memcpy(udp_hdr, data, len);
    udp_hdr->sp = ntohs(udp_hdr->sp);
    udp_hdr->tp = ntohs(udp_hdr->tp);
    udp_hdr->length = ntohs(udp_hdr->length);
    return udp_hdr;
}

int udp_checksum(Udp_Hdr *udp_hdr, uint16_t len)
{
    return checksum(udp_hdr, len);
}

void udp_print(Udp_Hdr *udp_hdr)
{
    printf("\t\tUDP Port: %u -> %u, Length: %u\n", udp_hdr->sp, udp_hdr->tp, udp_hdr->length);
}

Tcp_Hdr *tcp_parse(const unsigned char *data)
{
    Tcp_Hdr *tcp_hdr = malloc(sizeof(Tcp_Hdr));
    if (!tcp_hdr) LOG_ERROR("tcp_parse", "Allocation memory failed!");
    memcpy(tcp_hdr, data, sizeof(Tcp_Hdr));

    tcp_hdr->sp = ntohs(tcp_hdr->sp);
    tcp_hdr->tp = ntohs(tcp_hdr->tp);
    tcp_hdr->seq = ntohs(tcp_hdr->seq);
    tcp_hdr->ack = ntohs(tcp_hdr->ack);
    tcp_hdr->ff.v = ntohs(tcp_hdr->ff.v);
    tcp_hdr->ws = ntohs(tcp_hdr->ws);
    tcp_hdr->up = ntohs(tcp_hdr->up);
    return tcp_hdr;
}

void tcp_print(Tcp_Hdr *tcp_hdr)
{
    printf("\t\t\tTCP Port: %u -> %u\n", tcp_hdr->sp, tcp_hdr->tp);
}

int tcp_chechsum(Tcp_Hdr *tcp_hdr)
{
    return checksum(tcp_hdr, sizeof(Tcp_Hdr));
}

int host_mac(uint8_t *mac) {
    const char *sda = "80-30-49-02-DF-9D"; // TODO: 需要将静态的MAC地址改为动态获取
    for (int i = 0; i < ETH_II_MAC_LEN; ++i) {
        if (sscanf(sda + 3 * i, "%2hhx", &mac[i]) != 1) {
            return 1;
        }
    }
    return 0;
}