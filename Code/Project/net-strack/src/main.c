#include "devices.h"
#include "hdr.h"
#include "protocol.h"
#include "sock2.h"

#define USE_FILTER 1

void device_handle(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main() {
    int sockfd = socket2(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket2");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = bind2(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret != 0) {
        perror("bind2");
        return 1;
    }
    ret = listen2(sockfd, 5);
    if (ret != 0) {
        perror("listen2");
        return 1;
    }
    close2(sockfd);

    // =========device==============
    int ret;
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    ret = pcap_findalldevs(&alldevs, errbuf);
    if (ret) LOG_ERROR("pcap_findalldevs", errbuf);

    pcap_if_t *device = device_find(alldevs, "\\Device\\NPF_{134C479A-F628-4EB6-81C1-06406359BCDC}"); // TODO: 需要修改为动态获取网卡
    if (!device) LOG_ERROR("device_find", "The device does not exist!");

    pcap_t *handle = pcap_open_live(device->name, 65535/*整个数据包*/, 1/*混杂模式*/, 1000/*超时ms*/, errbuf);
    if (!handle) LOG_ERROR("pcap_open_live", errbuf);

#if USE_FILTER
    struct bpf_program bpf;
    char filter_exp[] = "udp";
    bpf_u_int32 net = 0;

    if (pcap_compile(handle, &bpf, filter_exp, 0, net) != 0) {
        LOG_ERROR("pcap_compile", pcap_geterr(handle));
    }

    if (pcap_setfilter(handle, &bpf) != 0) {
        LOG_ERROR("pcap_setfilter", pcap_geterr(handle));
    }
#endif // end of USE_FILTER

    ret = pcap_loop(handle, 5/*数据包*/, device_handle, NULL);
    if (ret) LOG_ERROR("pcap_loop", pcap_geterr(handle));

    // for (int i = 0; i < 10; ++i) arp_send(handle, NULL, ARP_GRATUITOUS); /* Send Gratuitous ARP */

    pcap_close(handle);
    pcap_freealldevs(device);
    return 0;
}

void device_handle(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    printf("\nPacket length: %d bytes.\n", header->len);

    const unsigned char *data = pkt_data;
    Stack *stack = stack_new();
    int top_type = SP_ETH;
    do {
        switch (top_type) {
            case SP_ETH: {
                EthII_Hdr *eth_ii = eth_ii_parse(data);

                // 获取上层协议类型
                if (eth_ii->type == ETH_II_TYPE_ARP) {
                    top_type = SP_ARP;
                } else if (eth_ii->type == ETH_II_TYPE_IPV4) {
                    top_type = SP_IPv4;
                } else if (eth_ii->type = ETH_II_TYPE_IPV6) {
                    top_type = SP_IPv6;
                } else {
                    LOG_ERROR("device_handle::eth_ii->type", "Unknow protocol type.");
                }
                stack_push(stack, eth_ii, SP_ETH, top_type);
                data += sizeof(EthII_Hdr); // Enthernet == +offset ==> ARP
                eth_ii_print(eth_ii);
                break;
            }
            case SP_ARP: {
                    Arp_Hdr *arp = arp_parse(data);
                    top_type = SP_NULL;
                    stack_push(stack, arp, SP_ARP, top_type);
                    data += sizeof(Arp_Hdr);
                    arp_print(arp);
                    break;
            }
            case SP_IPv4: {
                Ip_Hdr *ip_hdr = ip_parse(data);
                if (ip_hdr->protocol == IPPROTO_ICMP) {
                    top_type = SP_ICMP;
                } else if (ip_hdr->protocol == IPPROTO_TCP) {
                    top_type = SP_TCP;
                } else if (ip_hdr->protocol == IPPROTO_UDP) {
                    top_type = SP_UDP;
                } else {
                    LOG_ERROR("device_handle::eth_ii->type", "Unknow protocol type.");
                }
                stack_push(stack, ip_hdr, SP_IPv4, top_type);
                data += ip_hdr->ihl * 4;
                ip_print(ip_hdr);
                break;
            }
            case SP_ICMP: {
                const StackNode *node = stack_peek(stack);
                if (node == NULL) LOG_ERROR("ICMP", "Unable analysis icmp protocol.");
                const uint16_t len = ((Ip_Hdr*)node->data)->len - (((Ip_Hdr*)node->data)->ihl * 4);
                Icmp_Hdr *icmp_hdr = icmp_parse(data, len);
                top_type = SP_NULL;
                stack_push(stack, icmp_hdr, SP_ICMP, top_type);
                data += len;
                icmp_print(icmp_hdr);
                break;
            }
            case SP_UDP: {
                const StackNode *node = stack_peek(stack);
                if (node == NULL) LOG_ERROR("stack_peek", "Stack top is NULL!");
                const uint16_t len = ((Ip_Hdr*)node->data)->len - (((Ip_Hdr*)node->data)->ihl * 4); // FIX: 可能是长度计算错误
                Udp_Hdr *udp_hdr = udp_parse(data, len);
                top_type = SP_NULL;
                stack_push(stack, udp_hdr, SP_UDP, top_type);
                data += len;
                udp_print(udp_hdr);
                break;
            }
            case SP_TCP: {
                Tcp_Hdr *tcp_hdr = tcp_parse(data);
                top_type = SP_NULL;
                stack_push(stack, tcp_hdr, SP_TCP, top_type);
                data += sizeof(Tcp_Hdr);
                tcp_print(tcp_hdr);
                break;
            }
        }
    } while(top_type > 0);
}