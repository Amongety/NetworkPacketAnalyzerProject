#include "include/get_ip_for_mac_if.h"

int get_ip_address(struct ifreq *structpc) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd == -1) {
        printf("Error in the file \"get_ip_for_mac_if.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }
    
    if(ioctl(sockfd, SIOCGIFADDR, structpc) == -1) {
        printf("Error in the file \"get_ip_for_mac_if.c\" in the function \"ioctl\". Error: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}
