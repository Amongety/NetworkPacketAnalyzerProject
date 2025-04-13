#include "include/get_interface_lists.h"

int get_if_lists(struct ifconf* lists) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1) {
        printf("Error in the file \"get_interface_lists.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }

    if(ioctl(sockfd, SIOCGIFCONF, lists) == -1) {
        printf("Error in the file \"get_interface_lists.c\" in the function \"ioctl\". Error: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}
