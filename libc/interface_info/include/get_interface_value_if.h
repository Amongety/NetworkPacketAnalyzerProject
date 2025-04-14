#pragma once
#ifndef __GET_INTERFACE_VALUE_IF_H__
#define __GET_INTERFACE_VALUE_IF_H__ 1

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #define __USE_MISC 1
    #include <sys/ioctl.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <net/if.h>
    #include <unistd.h>
#elif _WIN32
    
#endif

int get_ivalue(struct ifreq* result);

#endif