#include "include/signal_handler.h"

void ft_fork_signal(int signo) {
    if(signo == SIGTSTP) {
        exit(0);
    }

    if(signo == SIGINT) {
        exit(0);
    }
}