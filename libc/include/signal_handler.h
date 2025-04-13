#pragma once
#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__ 1

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef __linux__

#elif _WIN32
    
#endif

void ft_fork_signal(int signo);

#endif