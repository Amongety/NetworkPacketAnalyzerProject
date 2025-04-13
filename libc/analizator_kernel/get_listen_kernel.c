#include "include/get_listen_kernel.h"

int kernel_socket(int sockfd, struct ifinfo infoPC) {
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sockfd == -1) {
        printf("Error in the file \"analizator.c\" in the function \"socket\"\n");
        close(sockfd);
        return -1;
    }

    struct sockaddr_ll s_ll;
    memset(&s_ll, 0, sizeof(s_ll));
    s_ll.sll_family = AF_PACKET;
    s_ll.sll_protocol = htons(ETH_P_ALL);
    s_ll.sll_ifindex = infoPC.ifru_ivalue;
    // s_ll.sll_hatype = ARPHRD_ETHER;
    // s_ll.sll_pkttype = PACKET_OTHERHOST;
    // s_ll.sll_halen = ETH_ALEN;
    // memcpy(s_ll.sll_addr, ((const struct ether_addr *)infoPC.ifru_hwaddr.sa_data)->ether_addr_octet, sizeof(s_ll.sll_addr));

    if(bind(sockfd, (struct sockaddr *)&s_ll, sizeof(s_ll)) == -1) {
        printf("Error in the file \"analizator.c\" in the function \"bind\"\n");
        close(sockfd);
        return -1;
    }
    
    return sockfd;
}
