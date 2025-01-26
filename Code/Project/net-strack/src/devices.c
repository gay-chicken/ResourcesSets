#include "devices.h"
#include "log.h"

void devices_info()
{
    int i = 0;
    pcap_if_t *all_devices;
    char eb[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&all_devices, eb) == -1)
    {
        LOG_ERROR("pcap_findalldevs_ex", eb);
    }

    for (const pcap_if_t *device = all_devices; device != NULL; device = device->next)
    {
        printf("%d. %s", ++i, device->name);
        if (device->description)
        {
            printf("(%s)\n", device->description);
        }
        else
        {
            printf("(No description)\n");
        }

        pcap_addr_t *addr;
        for (addr = device->addresses; addr != NULL; addr = addr->next) {
            if (addr->addr && addr->addr->sa_family == AF_INET) {
                struct sockaddr_in *ipaddr = (struct sockaddr_in *)addr->addr;
                struct sockaddr_in *netmask = (struct sockaddr_in *)addr->netmask;
                printf("\t\tIP Address: %s\n", inet_ntoa(ipaddr->sin_addr));
                if (netmask) {
                    printf("\t\tSubnet Mask: %s\n", inet_ntoa(netmask->sin_addr));
                }
            }
        }
    }

    if (i == 0)
    {
        printf("\nNo interfaces found! Make sure WinPacp is installed!\n");
        return;
    }

    pcap_freealldevs(all_devices);
}

pcap_if_t *device_find(pcap_if_t *alldevs, const char* uuid) {
    char errbuf[PCAP_ERRBUF_SIZE];

    for (pcap_if_t *device = alldevs; device != NULL; device = device->next) {
        if (!strcmp(device->name, uuid)) {
            return device;
        }
    }

    return NULL;
}