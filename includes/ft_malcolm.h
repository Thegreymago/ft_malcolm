#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* Inclusion des dépendances */

#define _GNU_SOURCE

# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <ifaddrs.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <net/if.h>
# include <net/ethernet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/if_ether.h>
# include <net/if_arp.h>
# include <sys/socket.h>
# include <linux/if_packet.h>
# include <net/ethernet.h>
# include "../libft/libft.h"


/* Définition des constantes */

# define PROGRAM "ft_malcolm"
# define BUFFER_SIZE 42 /* Struct ethhdr + struct arphdr + 6 + 4 + 6 + 4 */

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */

typedef struct arpheader
{
    unsigned short int ar_hrd;		/* Format of hardware address.  */
    unsigned short int ar_pro;		/* Format of protocol address.  */
    unsigned char ar_hln;		/* Length of hardware address.  */
    unsigned char ar_pln;		/* Length of protocol address.  */
    unsigned short int ar_op;		/* ARP opcode (command).  */
    unsigned char __ar_sha[ETH_ALEN];	/* Sender hardware address.  */
    unsigned char __ar_sip[4];		/* Sender IP address.  */
    unsigned char __ar_tha[ETH_ALEN];	/* Target hardware address.  */
    unsigned char __ar_tip[4];		/* Target IP address.  */
} t_arp;

typedef struct s_main
{
    char sourceMac[18];
    char sourceIp[16];
    char targetMac[18];
    char targetIp[16];
    int indexInterface;
    int sockfd;

}	t_main;

/* Prototype des fonctions */

// Source
int ft_malcolm(int argc, char **argv);
int handleErrorInput(int argc, char **argv);
int getNetworkInterface(t_main *main);
int setData(t_main *main, char **argv);
int sendArpReply(t_main *main);
int receiveArpRequest(t_main *main);
// Utils
void handleCtrlC(int data);
void display_network_interface(struct ifaddrs*);


#endif