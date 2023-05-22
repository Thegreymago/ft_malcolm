#include "../includes/ft_malcolm.h"


int getNetworkInterface()
{
    struct ifaddrs *ifap = NULL;

    struct addrinfo *result, *p;
    struct addrinfo hints;

    // struct hostent *res;

    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (getifaddrs(&ifap) == -1)
    {
        fprintf(stderr, "%s: getifaddrs failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }
    display_network_interface(ifap);

    // memset(&res, 0, sizeof res);
    // if ((res = gethostbyname("wlp4s0b1")) == NULL)
    // {
    //     fprintf(stderr, "%s: gethostbyname failed: %s\n", PROGRAM, strerror(errno));
    //     return -1;
    // }
    // printf("name = %s\n", res->h_name);

    // Configuration des hints pour filtrer les adresses IPv4
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_RAW;

    // Appel à getaddrinfo pour obtenir les adresses
    if ((status = getaddrinfo("10.12.3.7", NULL, &hints, &result)) != 0)
    {
        fprintf(stderr, "%s: getaddrinfo error: %s\n", PROGRAM, gai_strerror(status));
        return -1;
    }

    // Parcours des adresses obtenues
    for (p = result; p != NULL; p = p->ai_next)
    {
        void *addr;

        // Obtention de l'adresse IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        addr = &(ipv4->sin_addr);

        // Conversion de l'adresse en une représentation textuelle
        inet_ntop(AF_INET, addr, ipstr, sizeof ipstr);

        // Affichage de l'adresse
        printf("Interface: enp4s0f0\tAddress: %s (IPv4)\n", ipstr);
    }

    freeaddrinfo(result);
    return 0;
}