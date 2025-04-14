#include <stdlib.h>

#include "my_if.h"
#include "libc/include/get_if.h"
#include "libc/analizator_kernel/include/analizator.h"
#include "libc/include/signal_handler.h"

#ifdef __linux__
    #define _DEFAULT_SOURCE	1
    #include <net/if.h>
    #include <netinet/ether.h>
#elif _WIN32
    #include "winsock.h"
#endif

int main()
{
    // signal(SIGTSTP, ft_fork_signal);
    struct ifinfo* ifinfoPC = (struct ifinfo*)calloc(1, sizeof(struct ifinfo));
    get_ready_interface(ifinfoPC);

    printf("Interface number %d\n", ifinfoPC->ifru_ivalue);
    printf("Name %s\n", ifinfoPC->ifrn_name);
    printf("Flags %d\n", ifinfoPC->ifru_flags);
    printf("MTU %d\n", ifinfoPC->ifru_mtu);
    printf("Mac-addr %s\n", ether_ntoa((const struct ether_addr *)ifinfoPC->ifru_hwaddr.sa_data));
    printf("IPv4 %s\n", inet_ntoa(((struct sockaddr_in*)&ifinfoPC->ifru_addr)->sin_addr));
    printf("Broadcast %s\n", inet_ntoa(((struct sockaddr_in*)&ifinfoPC->ifru_broadaddr)->sin_addr));
    printf("NetMask %s\n", inet_ntoa(((struct sockaddr_in*)&ifinfoPC->ifru_netmask)->sin_addr));
    printf("\n");

    kernel_listening(*ifinfoPC);

    free(ifinfoPC);

    return 0;
}
