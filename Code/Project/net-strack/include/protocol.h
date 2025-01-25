#ifndef ETHII_H
#define ETHII_H

#include "hdr.h"
#include "stack.h"

char *ip2str(const uint32_t data);
char *mac2str(const unsigned char *mac);

int host_mac(uint8_t *mac);

EthII_Hdr *eth_ii_parse(const unsigned char *data);
void eth_ii_print(const EthII_Hdr *eth_ii);

Arp_Hdr *arp_parse(const unsigned char *data);
void arp_print(const Arp_Hdr *arp);
int arp_send(pcap_t *handle, char *tpa, uint8_t type);

Ip_Hdr *ip_parse(const unsigned char *data);
void ip_print(const Ip_Hdr *ip);
static uint16_t checksum(void *data, int len);
int ip_checksum(Ip_Hdr *ip_hdr);

Icmp_Hdr *icmp_parse(const unsigned char *data, uint16_t len);
int icmp_checksum(Icmp_Hdr *icmp, uint16_t len);
void icmp_print(const Icmp_Hdr *icmp);

Udp_Hdr *udp_parse(const unsigned char *data, uint16_t len);
int udp_checksum(Udp_Hdr *udp_hdr, uint16_t len);
void udp_print(Udp_Hdr *udp_hdr);

Tcp_Hdr *tcp_parse(const unsigned char *data);
void tcp_print(Tcp_Hdr *tcp_hdr);
int tcp_chechsum(Tcp_Hdr *tcp_hdr);
#endif // ETHII_H