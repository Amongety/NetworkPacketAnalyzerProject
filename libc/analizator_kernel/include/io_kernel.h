#pragma once
#ifndef __IO_KERNEL_H__
#define __IO_KERNEL_H__ 1

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "my_if.h"

#ifdef __linux__
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/ethernet.h>
    #include <netinet/ip.h>
    #include <netinet/ip6.h>
    #include <unistd.h>
#elif _WIN32
    #include "winsock.h"
#endif

int read_kernel(int sockfd);
// int write_kernel(int sockfd);

#endif