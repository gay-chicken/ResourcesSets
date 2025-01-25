#ifndef HDR_H
#define HDR_H

#include "pcap.h"

#define ETH_II_MAC_LEN 6

#define ARP_REQUEST 1
#define ARP_GRATUITOUS 2

#define ETH_II_TYPE_IPV4 0x0800
#define ETH_II_TYPE_IPV6 0x86DD
#define ETH_II_TYPE_ARP 0x0806

#define IPv4_VERSION 4
#define IPv6_VERSION 6

#define IP_TOP_ICMP 1
#define IP_TOP_TCP 6
#define IP_TOP_UDP 17

/* Ethernet data: [6-byte target_mac | 6-byte source_mac | 2-byte protocol_type ] */
typedef struct __attribute__((__packed__))
{
    uint8_t target_mac[ETH_II_MAC_LEN];
    uint8_t source_mac[ETH_II_MAC_LEN];
    uint16_t type;
} EthII_Hdr;

/**
 *          ARP Protocol
 * | HTYPE | PTYPE | HLEN | PLEN | OPER |
 * |             SHA             | SPA  |
 * | SPA |            THA               |
 * |      TPA      |
 *
 * HTYPE(2 byte): hardware type. Under normal conditions, assign 0x0001 as Ethernet.
 * PTYPE(2 byte): protocol type. IPv4 as 0x0800
 * HLEN(1 byte): hardware length
 * PLEN(1 byte): protocol length
 * OPER(2 byte): operator
 * SHA(6 byte): sender hardware address(MAC)
 * SPA(4 byte): sender ip address
 * THA(6 byte): target hardware address(MAC). For ARP request, this field is empty, except Gratuitous ARP request.
 * TPA(4 byte): target ip address
 */
typedef struct __attribute__((__packed__))
{
    uint16_t h_type;
    uint16_t p_type;
    uint8_t h_len;
    uint8_t p_len;
    uint16_t oper;
    uint8_t sha[ETH_II_MAC_LEN];
    uint32_t spa;
    uint8_t tha[ETH_II_MAC_LEN];
    uint32_t tpa;
} Arp_Hdr;

/**
 * IPv4 Protocol Header
 */
typedef struct __attribute__((__packed__))
{
    uint8_t ihl : 4;
    uint8_t version : 4;
    uint8_t tos;
    uint16_t len;
    uint16_t identification;
    union
    {
        uint16_t v;
        struct
        {
            uint16_t fo : 13;
            uint16_t flag : 3;
        };
    } ff; /* Flag & Fragment Offset*/
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src;
    uint32_t dst;
} Ip_Hdr;

/**
 * ICMP protocol header
 * | TYPE | CODE | Checksum | Message Body |
 *
 * TYPE(8-bit): 消息类型，用于表示ICMP的功能
 * CODE(8-bit): 子类型，进一步说明消息类型
 * Checksum(16-bit): 校验和，验证数据完整性，包含数据部分。
 * Message Body(可变): 可选项。包含具体的ICMP消息内容，例如IP头部或时间戳信息。
 */
typedef struct __attribute__((__packed__))
{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint8_t data[];
} Icmp_Hdr;

typedef struct __attribute__((__packed__))
{
    uint16_t sp;
    uint16_t tp;
    uint16_t length;
    uint16_t checksum;
    uint8_t data[];
} Udp_Hdr;

typedef struct __attribute__((__packed__))
{
    uint16_t sp;
    uint16_t tp;
    uint32_t seq;
    uint32_t ack;
    union
    {
        uint16_t v;
        struct
        {
            uint16_t flags : 6;
            uint16_t unused : 6;
            uint16_t offset : 4;
        };
    } ff;
    uint16_t ws;
    uint16_t checksum;
    uint16_t up;
} Tcp_Hdr;
#endif // HDR_H