#ifndef DEVICES_H
#define DEVICES_H

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define HAVE_REMOTE
#define WPCAP
#include "pcap.h"
#include "log.h"

void devices_info();
pcap_if_t *device_find(pcap_if_t *alldevs, const char* uuid);

#endif