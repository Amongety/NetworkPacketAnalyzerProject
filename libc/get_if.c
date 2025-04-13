#include "include/get_if.h"

#include "../libc/interface_info/include/get_flags_if.h"
#include "../libc/interface_info/include/get_interface_lists.h"
#include "../libc/interface_info/include/get_mac_address_if.h"
#include "../libc/interface_info/include/get_ip_for_mac_if.h"
#include "../libc/interface_info/include/get_broadcast_if.h"
#include "../libc/interface_info/include/get_mtu_if.h"
#include "../libc/interface_info/include/get_network_mask_if.h"
#include "../libc/interface_info/include/get_interface_value_if.h"

int get_ready_interface(struct ifinfo* infoPC) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    char *buff;
    struct ifconf arrayif;
    memset(&arrayif, 0, sizeof(struct ifconf));

    if(sockfd == -1) {
        printf("Error in the file \"get_if.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }

    if(get_if_lists(&arrayif) == -1) return -1;

    if(arrayif.ifc_ifcu.ifcu_req == NULL) {
        buff = (char*)malloc(arrayif.ifc_len);
        arrayif.ifc_ifcu.ifcu_buf = buff;
    }

    if(get_if_lists(&arrayif) == -1) return -1;

    for(struct ifreq* next = (struct ifreq*)buff; (char*)next < buff + arrayif.ifc_len; next = (struct ifreq*)((char*)next + sizeof(*next))) {
        if(get_flags(next) == -1) return -1;

        if((next->ifr_ifru.ifru_flags & IFF_UP) && (next->ifr_ifru.ifru_flags & IFF_BROADCAST) && (next->ifr_ifru.ifru_flags & IFF_RUNNING) && (next->ifr_ifru.ifru_flags & IFF_MULTICAST)) {
            memcpy(infoPC->ifrn_name, next->ifr_ifrn.ifrn_name, IFNAMSIZ);
            memcpy(&infoPC->ifru_flags, &next->ifr_ifru.ifru_flags, sizeof(short int));

            if(get_mac(next) == -1) return -1;
            memcpy(&infoPC->ifru_hwaddr, &next->ifr_ifru.ifru_hwaddr, sizeof(struct sockaddr));

            if(get_ip_address(next) == -1) return -1;
            memcpy(&infoPC->ifru_addr, &next->ifr_ifru.ifru_addr, sizeof(struct sockaddr));

            if(get_broadcast(next) == -1) return -1;
            memcpy(&infoPC->ifru_broadaddr, &next->ifr_ifru.ifru_broadaddr, sizeof(struct sockaddr));

            if(get_mtu(next) == -1) return -1;
            memcpy(&infoPC->ifru_mtu, &next->ifr_ifru.ifru_mtu, sizeof(int));

            if(get_netmask(next) == -1) return -1;
            memcpy(&infoPC->ifru_netmask, &next->ifr_ifru.ifru_netmask, sizeof(struct sockaddr));

            if(get_ivalue(next) == -1) return -1;
            memcpy(&infoPC->ifru_ivalue, &next->ifr_ifru.ifru_ivalue, sizeof(int));

            break;
        }
    }

    free(buff);
    close(sockfd);
    return 0;
}
