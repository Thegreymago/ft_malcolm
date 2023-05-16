#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* Inclusion des dépendances */

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/if_ether.h>
# include <net/if_arp.h>
# include <sys/socket.h>
// # include <linux/if_packet.h>
# include <net/ethernet.h>
# include "../libft/libft.h"




/* Définition des constantes */

# define ARG "Error\nIncorrect number of arguments\n"

# define BUFFER_SIZE 65536


/* Déclaration des structures */

typedef struct s_main
{
    char *sourceMac;
    char *sourceIp;
    char *targetMac;
    char *targetIp;

}	t_main;

/* Prototype des fonctions */

void handleCtrlC(int data);

#endif