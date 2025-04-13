#include "include/get_flags_if.h"

int get_flags(struct ifreq* result) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1) {
        printf("Error in the file \"get_flags_if.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }

    if(ioctl(sockfd, SIOCGIFFLAGS, result) == -1) {
        printf("Error in the file \"get_flags_if.c\" in the function \"ioctl\". Error: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}
