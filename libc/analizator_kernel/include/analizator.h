#pragma once
#ifndef __ANALIZATOR_H__
#define __ANALIZATOR_H__ 1

#include <stdlib.h>
#include <stdio.h>

#include "my_if.h"

#ifdef __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/ethernet.h>
    #include <unistd.h>
#elif _WIN32
    #include "winsock.h"
#endif

int kernel_listening(struct ifinfo infoPC);

#endif