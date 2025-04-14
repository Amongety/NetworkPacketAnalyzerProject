#include "include/transport_processing.h"

int transport_handler_layer_ipv4(int indification, char *buff, int rbytes) {
    switch(indification) {
        case IPPROTO_TCP:
            struct tcphdr *tcp_segments = (struct tcphdr*)(buff + sizeof(struct ether_header) + sizeof(struct ip));

            printf("\tTCP\t\nSource port: %d\nDestination port: %d\nSequence number: %ld\nAcknowledgement number: %ld\n"
                "Header length: %d\nFlags:\n\tReserved: %d\n\tAccurate: %d\n\tCongestion window: %d\n\tECN-echo: %d\n\t"
                "Urgent: %d\n\tAcknowledgment: %d\n\tPush: %d\n\tReset: %d\n\tSyn: %d\n\tFin: %d\nWindow: %d\nChecksum: %d\n"
                "Urgent pointer: %d\nTCP payload: %d\n", \
                htons(tcp_segments->th_sport), htons(tcp_segments->th_dport), htonl(tcp_segments->th_seq), htonl(tcp_segments->th_ack), \
                tcp_segments->th_off, (tcp_segments->res1 & 0xE) >> 1, tcp_segments->res1 & 0x1, (tcp_segments->res2 & 0x2) >> 1, \
                tcp_segments->res2 & 0x1, tcp_segments->urg, tcp_segments->ack, tcp_segments->psh, tcp_segments->rst, \
                tcp_segments->syn, tcp_segments->fin, htons(tcp_segments->th_win), htons(tcp_segments->th_sum), htons(tcp_segments->th_urp), \
                rbytes - sizeof(struct ether_header) - sizeof(struct ip) - (tcp_segments->th_off * 4));

            // printf("TCP useful data:\n");
            // for(int i = sizeof(struct ether_header) - sizeof(struct ip) - (tcp_segments->th_off * 4); i < rbytes; ++i) printf("%c", buff[i]);
            // printf("\n");
            break;

        case IPPROTO_UDP:
            struct udphdr *udp_segments = (struct udphdr*)(buff + sizeof(struct ether_header) + sizeof(struct ip));

            printf("\tUDP\t\nSource port: %d\nDestination port: %d\nLength: %d\nChecksum: %d\nUDP payload: %d\n", \
                htons(udp_segments->uh_sport), htons(udp_segments->uh_dport), htons(udp_segments->uh_ulen), \
                htons(udp_segments->uh_sum), rbytes - sizeof(struct udphdr) - sizeof(struct ether_header) - sizeof(struct ip));
            
            printf("UDP useful data:\n");
            for(int i = sizeof(struct udphdr) + sizeof(struct ip) + sizeof(struct ether_header); i < rbytes; ++i) printf("%c", buff[i]);
            printf("\n");
            break;

        case IPPROTO_IGMP:
            struct igmp *igmp_segments = (struct igmp*)(buff + sizeof(struct ether_header) + sizeof(struct ip) + 4);

            if(igmp_segments->igmp_type == 0x11) {
                struct igmpv3qeury *igmp_query = (struct igmpv3qeury*)(buff + sizeof(struct ether_header) + sizeof(struct ip) + 4);

                char *multiip = (char*)malloc(sizeof(char) * 16);
                memset(multiip, 0, sizeof(multiip));

                inet_ntop(AF_INET, &igmp_query->igmp_group, multiip, 16);

                printf("\tIGMP\t\nType: %d\nMax resp time: %d\nChecksum: %d\nMulticast addres: %s\nFlags: %d\n"
                    "\tSuppress router side processing: %d\n\tQRV: %d\nQQIC: %d\nNumber sorce: %d\n", \
                    igmp_query->igmp_type, igmp_query->res_time, htons(igmp_query->igmp_cksum), multiip, igmp_query->flags, \
                    (igmp_query->flags & 0x8) >> 3, igmp_query->flags & 0x7, igmp_query->qquic, htons(igmp_query->snum));
                
                free(multiip);
            }

            else if(igmp_segments->igmp_type == 0x22) {
                struct igmpv3report *igmp_report = (struct igmpv3report*)(buff + sizeof(struct ether_header) + sizeof(struct ip) + 4);

                char *multiip = (char*)malloc(sizeof(char) * 16);
                memset(multiip, 0, sizeof(multiip));

                inet_ntop(AF_INET, &igmp_report->igmp_multicast, multiip, 16);

                printf("\tIGMP\t\nType: %d\nReserved: %d\nChecksum: %d\nReserved: %d\nNum group records: %d\nRecord type: %d\nAux data len: %d\n"
                    "Number source: %d\nMulticast addres: %s\n", igmp_report->igmp_type, igmp_report->res1, \
                    htons(igmp_report->igmp_cksum), htons(igmp_report->res2), htons(igmp_report->grecords), igmp_report->rtype, igmp_report->dlen, htons(igmp_report->nsrc), multiip);

                free(multiip);
            }

            else {
                printf("Application does not support (OSI transport: IGMP)\n");
                return -1;
            }
            break;

        case IPPROTO_ICMP:
            struct icmphdr *icmp = (struct icmphdr*)(buff + sizeof(struct ether_header) + sizeof(struct ip));

            printf("\tICMP\t\nType: %d\nCode: %d\nChecksum: %d\nIdentifier: %d\nSequence number: %d\n", icmp->type, icmp->code, htons(icmp->checksum), \
            htons(icmp->un.echo.id), htons(icmp->un.echo.sequence));
            break;

        default:
            printf("Application does not support (OSI transport)Type: %d\n", indification);
            return -1;
    }

    return 0;
}

int transport_handler_layer_ipv6(int indification, char *buff, int rbytes) {
    switch(indification) {
        case IPPROTO_UDP:
            struct udphdr *udp_segments = (struct udphdr*)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr));

            printf("\tUDP\t\nSource port: %d\nDestination port: %d\nLength: %d\nChecksum: %d\nUDP payload: %d\n", \
                htons(udp_segments->uh_sport), htons(udp_segments->uh_dport), htons(udp_segments->uh_ulen), \
                htons(udp_segments->uh_sum), rbytes - sizeof(struct udphdr) - sizeof(struct ether_header) - sizeof(struct ip6_hdr));
            
            printf("UDP useful data:\n");
            for(int i = sizeof(struct udphdr) + sizeof(struct ip6_hdr) + sizeof(struct ether_header); i < rbytes; ++i) printf("%c", buff[i]);
            printf("\n");
            break;

        case IPPROTO_ICMPV6:
            struct icmp6_hdr *icmp6_segments = (struct icmp6_hdr *)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr));

            if(icmp6_segments->icmp6_type == ND_ROUTER_SOLICIT) {
                struct icmp6_hdr_router *icmp6_v2 = (struct icmp6_hdr_router*)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr));

                printf("\tICMPV6\t\nType: %d\nCode: %d\nChecksum: %d\nReserved: %d\n", \
                    icmp6_v2->icmp6_type, icmp6_v2->icmp6_code, htons(icmp6_v2->icmp6_cksum), htonl(icmp6_v2->res1));
            }

            else if(icmp6_segments->icmp6_type == IPPROTO_MH) {
                struct icmp6_ns *icmp6_ns_segments = (struct icmp6_ns *)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr));

                char *target_ip6 = (char*)malloc(sizeof(char) * 40);
                memset(target_ip6, 0, 40);

                inet_ntop(AF_INET6, &icmp6_ns_segments->target_addr, target_ip6, 40);

                printf("\tICMPV6\t\nType: %d\nCode: %d\nChecksum: %d\nReserved: %d\nTraget address: %s\nType: %d\nLength: %d\n", \
                    icmp6_ns_segments->icmp6_type, icmp6_ns_segments->icmp6_code, \
                    htons(icmp6_ns_segments->icmp6_cksum), htonl(icmp6_ns_segments->res1), target_ip6, icmp6_ns_segments->opt_type, icmp6_ns_segments->opt_length);

                free(target_ip6);
            }

            else {
                printf("Application does not support (OSI transport: ICMPV6)Type: %d\n", icmp6_segments->icmp6_type);
                return -1;
            }
            break;
        
        case IPPROTO_HOPOPTS:
            struct icmp6_hdr *ipv6_hop_segments = (struct icmp6_hdr *)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr));    

            if(ipv6_hop_segments->icmp6_type == 58) {
                struct icmp6_hdr_v2 *mlrm_v2 = (struct icmp6_hdr_v2*)(buff + sizeof(struct ether_header) + sizeof(struct ip6_hdr) + 8);

                char *multi_addr6 = (char*)malloc(sizeof(char) * 40);
                memset(multi_addr6, 0, 40);

                inet_ntop(AF_INET6, &mlrm_v2->multi_addr, multi_addr6, 40);

                printf("\tICMPV6\t\nType: %d\nCode: %d\nChecksum: %d\nReserved: %d\nNumber of multicast address records: %d\n"
                    "Record type: %d\nAux data len: %d\nNumber of sources: %d\nMulticast address: %s\n", \
                    mlrm_v2->icmp6_type, mlrm_v2->icmp6_code, htons(mlrm_v2->icmp6_cksum), \
                    htons(mlrm_v2->res1), htons(mlrm_v2->addrrec), mlrm_v2->rtype, mlrm_v2->dlen, htons(mlrm_v2->nsources), multi_addr6);

                free(multi_addr6);
            }

            else {
                printf("Application does not support (OSI transport: HOP-BY-HOP)\n");
                return -1;
            }
            break;

        default:
            printf("Application does not support protocol\n");
            return -1;
    }

    return 0;
}
