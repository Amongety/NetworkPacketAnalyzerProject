#pragma once
#ifndef __NETWORK_PCOSSENIG_H__
#define __NETWORK_PCOSSENIG_H__ 1

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "my_if.h"

#ifdef __linux__
    #include <arpa/inet.h>
    #include <netinet/ether.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/ethernet.h>
    #include <netinet/ip.h>
    #include <netinet/ip6.h>
#elif _WIN32
    
#endif

int network_handler_layer(int indification, char *buff, int rbytes);

#endif