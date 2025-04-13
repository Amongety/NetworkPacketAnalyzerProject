#pragma once
#ifndef __GET_MAC_ADDRESS_IF_H__
#define __GET_MAC_ADDRESS_IF_H__ 1

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #define __USE_MISC 1
    #include <netinet/ether.h>
    #include <sys/ioctl.h>
    #include <net/if.h>
    #include <netinet/in.h>
#elif _WIN32
    
#endif

int get_mac(struct ifreq* result);

#endif