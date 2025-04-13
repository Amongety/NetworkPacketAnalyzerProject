#include "include/network_processing.h"
#include "include/transport_processing.h"

int network_handler_layer(int indification, char *buff, int rbytes) {
    switch(indification) {
        case ETHERTYPE_ARP:
            struct arphdr_old *packet_arp = (struct arphdr_old*)(buff + sizeof(struct ether_header));

            char *macsrc = (char*)malloc(sizeof(char) * 18), *macdst = (char*)malloc(sizeof(char) * 18), *ipsrc_arp = (char*)malloc(sizeof(char) * 16), *ipdst_arp = (char*)malloc(sizeof(char) * 16);
            memset(macsrc, 0, 18);
            memset(macdst, 0, 18);
            memset(ipsrc_arp, 0, 16);
            memset(ipdst_arp, 0, 16);

            inet_ntop(AF_INET, packet_arp->__ar_sip, ipsrc_arp, 16);
            inet_ntop(AF_INET, packet_arp->__ar_tip, ipdst_arp, 16);
            ether_ntoa_r((const struct ether_addr*)packet_arp->__ar_sha, macsrc);
            ether_ntoa_r((const struct ether_addr*)packet_arp->__ar_tha, macdst);

            printf("\tARP\t\nHradware type: %d\nProtocol type: %d\nHardware size: %d\nProtocol size: %d\nOpcode: %d\n"
                "Sender MAC: %s\nSender IP: %s\nTarget MAC: %s\nTraget IP: %s\n", \
                htons(packet_arp->ar_hrd), htons(packet_arp->ar_pro), packet_arp->ar_hln, packet_arp->ar_pln, htons(packet_arp->ar_op), \
                macsrc, ipsrc_arp, macdst, ipdst_arp);

            free(macsrc);
            free(macdst);
            free(ipsrc_arp);
            free(ipdst_arp);
            break;

        case ETHERTYPE_IP:
            struct ip *packet_ip = (struct ip*)(buff + sizeof(struct ether_header));

            char *ipsrc = (char*)malloc(sizeof(char) * 16), *ipdst = (char*)malloc(sizeof(char) * 16);
            memset(ipsrc, 0, 16);
            memset(ipdst, 0, 16);

            inet_ntop(AF_INET, &packet_ip->ip_src, ipsrc, 16);
            inet_ntop(AF_INET, &packet_ip->ip_dst, ipdst, 16);

            printf("\tIPv4\t\nVersion: %d\nHeader Lenght: %d\nType of service: %d\nTotal Length: %d\nIdentification: %d\n"
                "Flags: %d\n\tReserved bit: %d\n\tDont fragment: %d\n\tMore fragments: %d\nFragment offset: %d\nTime to live: %d\n"
                "Protocol: %d\nCheksum: %d\nSource IPv4: %s\nDestination IPv4: %s\n", \
                packet_ip->ip_v, packet_ip->ip_hl, packet_ip->ip_tos, htons(packet_ip->ip_len), htons(packet_ip->ip_id), \
                (htons(packet_ip->ip_off) & 0xE000) >> 13, (htons(packet_ip->ip_off) & IP_RF) >> 15, \
                (htons(packet_ip->ip_off) & IP_DF) >> 14, (htons(packet_ip->ip_off) & IP_MF) >> 13, htons(packet_ip->ip_off) & 0x1FFF, packet_ip->ip_ttl, packet_ip->ip_p, \
                htons(packet_ip->ip_sum), ipsrc, ipdst);

            free(ipsrc);
            free(ipdst);

            if(transport_handler_layer_ipv4(packet_ip->ip_p, buff, rbytes) == -1) return -1;
            break;

        case ETHERTYPE_IPV6:
            struct ip6_hdr *packet_ip6 = (struct ip6_hdr*)(buff + sizeof(struct ether_header));

            char *ip6src = (char*)malloc(sizeof(char) * 40), *ip6dst = (char*)malloc(sizeof(char) * 40);
            memset(ip6src, 0, 40);
            memset(ip6dst, 0, 40);

            inet_ntop(AF_INET6, &packet_ip6->ip6_src, ip6src, 40);
            inet_ntop(AF_INET6, &packet_ip6->ip6_dst, ip6dst, 40);

            printf("\tIPv6\t\nVersion: %d\nTraffic class: %d\nFlow label: %d\nPayload length: %d\nNext header: %d\n"
            "Hop limit: %d\nSource IPv6: %s\nDestination IPv6: %s\n", \
            htonl(packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_flow) >> 28, \
            (htonl(packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_flow) & 0xFF00000) >> 20, htonl(packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_flow) & 0xFFFFF, \
            htons(packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_plen), packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_nxt, packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_hlim, \
            ip6src, ip6dst);

            free(ip6src);
            free(ip6dst);

            if(transport_handler_layer_ipv6(packet_ip6->ip6_ctlun.ip6_un1.ip6_un1_nxt, buff, rbytes) == -1) return -1;
            break;

        default:
            printf("Application does not support (OSI network)\n");
            return -1;
    }
    
    return 0;
}
