#pragma once
#ifndef __GET_LISTEN_KERNEL_H__
#define __GET_LISTEN_KERNEL_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_if.h"

#ifdef __linux__
    #include <linux/if_packet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/ethernet.h>
    #include <linux/if_arp.h>
    #include <unistd.h>
#elif _WIN32
    
#endif

int kernel_socket(int sockfd, struct ifinfo);

#endif