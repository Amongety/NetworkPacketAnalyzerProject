#pragma once
#ifndef __TRANPORT_PROCESSING_H__
#define __TRANPORT_PROCESSING_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_if.h"

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #include <linux/if_packet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/ethernet.h>
    #include <netinet/tcp.h>
    #include <netinet/udp.h>
    #include <netinet/ip.h>
    #include <netinet/ip6.h>
    #include <netinet/igmp.h>
    #include <arpa/inet.h>
    #include <netinet/icmp6.h>
    #include <netinet/ip_icmp.h>
    #include <unistd.h>
#elif _WIN32
    
#endif

int transport_handler_layer_ipv4(int indification, char *buff, int rbytes);
int transport_handler_layer_ipv6(int indification, char *buff, int rbytes);

#endif