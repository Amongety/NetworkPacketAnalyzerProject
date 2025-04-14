#pragma once
#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__ 1

#include <signal.h>
#include <stdlib.h>

#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include "winsock.h"
#endif

void ft_fork_signal(int signo);

#endif