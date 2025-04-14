#pragma once
#ifndef __MY_IF_H__
#define __MY_IF_H__ 1

#include <stdint.h>

#ifdef __linux__
    #include <sys/socket.h>
    #include <net/if.h>
    #include <netinet/in.h>
#elif _WIN32
    #include "winsock.h"
#endif

/* struct ifreq */
struct ifinfo {
    # define IFHWADDRLEN	6
    # define IFNAMSIZ	IF_NAMESIZE
	char ifrn_name[IFNAMSIZ];	    /* Interface name, e.g. "en0".  */

	struct sockaddr ifru_addr;
	struct sockaddr ifru_dstaddr;
	struct sockaddr ifru_broadaddr;
	struct sockaddr ifru_netmask;
	struct sockaddr ifru_hwaddr;
	short int ifru_flags;
	int ifru_ivalue;
	int ifru_mtu;
	struct ifmap ifru_map;
	char ifru_slave[IFNAMSIZ];	    /* Just fits the size */
	char ifru_newname[IFNAMSIZ];
	__caddr_t ifru_data;
};

struct arphdr_old {
    #define ETH_ALEN    6
    unsigned short int ar_hrd;		/* Format of hardware address.  */
    unsigned short int ar_pro;		/* Format of protocol address.  */
    unsigned char ar_hln;		    /* Length of hardware address.  */
    unsigned char ar_pln;		    /* Length of protocol address.  */
    unsigned short int ar_op;		/* ARP opcode (command).  */
    /* Ethernet looks like this : This bit is variable sized
       however...  */
    unsigned char __ar_sha[ETH_ALEN];	/* Sender hardware address.  */
    unsigned char __ar_sip[4];		    /* Sender IP address.  */
    unsigned char __ar_tha[ETH_ALEN];	/* Target hardware address.  */
    unsigned char __ar_tip[4];		    /* Target IP address.  */
};

struct igmpv3qeury {
    uint8_t igmp_type;              /* IGMP type */
    uint8_t res_time;               /* maximum response time */
    uint16_t igmp_cksum;            /* checksum */
    struct in_addr igmp_group;      /* group address */
    uint8_t flags;                  /* Flags bits: 
                                    .... 0...   .... .000 */
    uint8_t qquic;                  /* Request interval code */
    uint16_t snum;                  /* num src */
};

struct igmpv3report {
    uint8_t igmp_type;                  /* IGMP type */
    uint8_t res1;                       /* reserved */
    uint16_t igmp_cksum;                /* checksum */
    uint16_t res2;                      /* reserved */
    uint16_t grecords;                  /* number group records */
    uint8_t rtype;                      /* record type */
    uint8_t dlen;                       /* aux data len */
    uint16_t nsrc;                      /* number source */
    struct in_addr igmp_multicast;      /* multicast address */
};

struct icmp6_hdr_v2 {
    uint8_t icmp6_type;             /* type field */
    uint8_t icmp6_code;             /* code field */
    uint16_t icmp6_cksum;           /* checksum field */
    uint16_t res1;                  /* reserved */
    uint16_t addrrec;               /* number of multicast address records */
    uint8_t rtype;                  /* record type */
    uint8_t dlen;                   /* aux data len */
    uint16_t nsources;              /* number of sources */  
    struct in6_addr multi_addr;     /* multicast address */
};

struct icmp6_hdr_router {
    uint8_t icmp6_type;         /* type field */
    uint8_t icmp6_code;         /* code field */
    uint16_t icmp6_cksum;       /* checksum field */
    uint32_t res1;              /* reserved */
};

/* Neighbor solicitation */
struct icmp6_ns {
    uint8_t icmp6_type;             /* type field */
    uint8_t icmp6_code;             /* code field */
    uint16_t icmp6_cksum;           /* checksum field */
    uint32_t res1;                  /* reserved */
    struct in6_addr target_addr;    /* target address*/
    uint8_t opt_type;               /* option type */
    uint8_t opt_length;             /* oprion length */
};

#endif