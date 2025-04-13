#pragma once
#ifndef __GET_IF_H__
#define __GET_IF_H__ 1

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "my_if.h"

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #define __USE_MISC 1
    #include <sys/ioctl.h>
    #include <net/if.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
#elif _WIN32
    
#endif

int get_ready_interface(struct ifinfo* infoPC);

#endif