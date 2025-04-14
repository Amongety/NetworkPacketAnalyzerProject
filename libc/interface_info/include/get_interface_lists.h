#pragma once
#ifndef __GET_INTERFACE_LISTS_H__
#define __GET_INTERFACE_LISTS_H__ 1

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
    #include "winsock.h"
#endif

int get_if_lists(struct ifconf* lists);

#endif