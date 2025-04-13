#pragma once
#ifndef __GET_NETWORK_MASK_IF_H__
#define __GET_NETWORK_MASK_IF_H__ 1

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #define __USE_MISC 1
    #include <sys/ioctl.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <net/if.h>
#elif _WIN32
    
#endif

int get_netmask(struct ifreq* result);

#endif