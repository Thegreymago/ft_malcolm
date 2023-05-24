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

# define BUFFER_SIZE 65536

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */

typedef struct s_main
{
    in_addr_t sourceMac;
    in_addr_t sourceIp;
    in_addr_t targetMac;
    in_addr_t targetIp;
    char interfaceName[IF_NAMESIZE];

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