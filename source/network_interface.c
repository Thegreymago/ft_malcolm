#include "../includes/ft_malcolm.h"


int getNetworkInterface()
{
    struct ifaddrs *ifap = NULL;

    struct addrinfo *result, *p;
    struct addrinfo hints;

    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (getifaddrs(&ifap) == -1)
    {
        fprintf(stderr, "%s: getifaddrs failed: %s\n", PROGRAM ,strerror(errno));
        return -1;
    }
    display_network_interface(ifap);

    // Configuration des hints pour filtrer les adresses IPv4
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_RAW;

    // Appel à getaddrinfo pour obtenir les adresses
    if ((status = getaddrinfo("enp4s0f0", NULL, &hints, &result)) != 0) {
        fprintf(stderr, "%s: getaddrinfo error: %s\n", PROGRAM ,gai_strerror(status));
        return -1;
    }

    // Parcours des adresses obtenues
    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // Obtention de l'adresse IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";

        // Conversion de l'adresse en une représentation textuelle
        inet_ntop(AF_INET, addr, ipstr, sizeof ipstr);

        // Affichage de l'adresse
        printf("Interface: enp4s0f0\tAddress: %s (%s)\n", ipstr, ipver);
    }

    freeaddrinfo(result);
    return 0;
}