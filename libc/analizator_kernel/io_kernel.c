#include "include/network_processing.h"
#include "include/io_kernel.h"

int read_kernel(int sockfd) {
    char *buff_read;

    while(1) {
        buff_read = (char*)malloc(4096 * sizeof(char));
        memset(buff_read, 0, 4096);

        int s = recvfrom(sockfd, buff_read, 4096, 0, NULL, NULL);

        if(s > 0) {
            struct ether_header *frame_ether = (struct ether_header*)(buff_read);

            char *macsrc = (char*)malloc(sizeof(char) * 18), *macdst = (char*)malloc(sizeof(char) * 18);
            memset(macsrc, 0, 18);
            memset(macdst, 0, 18);

            ether_ntoa_r((const struct ether_addr*)frame_ether->ether_shost, macsrc);
            ether_ntoa_r((const struct ether_addr*)frame_ether->ether_dhost, macdst);

            printf("\tETHERNET\t\nSource MAC: %s\tDestination MAC: %s\tType: %d\n", macsrc, macdst, htons(frame_ether->ether_type));

            free(macsrc);
            free(macdst);

            if(network_handler_layer(htons(frame_ether->ether_type), buff_read, s) == -1) {
                free(buff_read);
                return -1;        
            }
        }

        free(buff_read);
    }
    
    return 0;
}

// int write_kernel(int sockfd) {
//     char *buff_write;
//     buff_write = (char*)malloc(4096 * sizeof(char));
//     memset(buff_write, 0, 4096);

//     // sendto();

//     free(buff_write);
// }
