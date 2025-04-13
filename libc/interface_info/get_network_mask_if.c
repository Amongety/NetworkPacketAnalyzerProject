#include "include/get_network_mask_if.h"

int get_netmask(struct ifreq* result) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1) {
        printf("Error in the file \"get_network_mask_if.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }

    if(ioctl(sockfd, SIOCGIFNETMASK, result) == -1) {
        printf("Error in the file \"get_network_mask_if.c\" in the function \"ioctl\". Error: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}