#include "../includes/ft_malcolm.h"

// int getAllIpNetwork() 
// {
//     struct addrinfo hints, *res, *p;
//     int status;
//     char ipstr[INET6_ADDRSTRLEN];

//     // Remplir la structure hints avec les informations souhaitées
//     memset(&hints, 0, sizeof hints);
//     hints.ai_family = AF_UNSPEC;  // Permet à getaddrinfo() de supporter IPv4 et IPv6
//     hints.ai_socktype = SOCK_STREAM;  // Utiliser SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP

//     // Résolution de l'interface réseau
//     if ((status = getaddrinfo("eth0", NULL, &hints, &res)) != 0) {
//         fprintf(stderr, "Erreur lors de la résolution de l'interface : %s\n", gai_strerror(status));
//         return 1;
//     }

//     printf("Adresses IP pour l'interface eth0 :\n\n");

//     // Parcourir les résultats et afficher les adresses IP
//     for (p = res; p != NULL; p = p->ai_next) {
//         void *addr;
//         char *ipver;

//         // Obtenir l'adresse IPv4 ou IPv6
//         if (p->ai_family == AF_INET) {  // IPv4
//             struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
//             addr = &(ipv4->sin_addr);
//             ipver = "IPv4";
//         } else {  // IPv6
//             struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
//             addr = &(ipv6->sin6_addr);
//             ipver = "IPv6";
//         }

//         // Convertir l'adresse IP en une chaîne de caractères lisible
//         inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
//         printf("%s: %s\n", ipver, ipstr);
//     }

//     freeaddrinfo(res);  // Libérer la mémoire allouée par getaddrinfo

//     return 0;
// }

int sameNetwork(uint32_t ip1, uint32_t ip2, uint32_t mask) {
    return (ip1 & mask) == (ip2 & mask);
}

int getNetworkInterface(t_main *main)
{
    struct ifaddrs *ifap = NULL;
    in_addr_t sourceIp = inet_addr(main->sourceIp);
    in_addr_t targetIp = inet_addr(main->targetIp);
    int sourceCount = 0;
    int targetCount = 0;

    if (getifaddrs(&ifap) == -1)
    {
        fprintf(stderr, "%s: getifaddrs failed: %s\n", PROGRAM, strerror(errno));
        freeifaddrs(ifap);
        return -1;
    }

    /* BOUCLE IMBRIQUE POUR PARCOURIR LES INTERFACE IP ET ARP */
    for (struct ifaddrs *ifaptmp = ifap; ifaptmp; ifaptmp = ifaptmp->ifa_next)
    {
        if (ifaptmp && ifaptmp->ifa_addr && ifaptmp->ifa_netmask && ifaptmp->ifa_addr->sa_family == AF_INET)
        {
            uint32_t networkIP = ((struct sockaddr_in *)ifaptmp->ifa_addr)->sin_addr.s_addr;
            uint32_t networkMask = ((struct sockaddr_in *)ifaptmp->ifa_netmask)->sin_addr.s_addr;
            
            if (sameNetwork(networkIP, sourceIp, networkMask))
            {
                sourceCount++;
                if (sameNetwork(networkIP, targetIp, networkMask))
                {
                    targetCount++;
                    for (struct ifaddrs *ifaptmp2 = ifap; ifaptmp2; ifaptmp2 = ifaptmp2->ifa_next)
                    {
                        if (ifaptmp2 && !ft_memcmp(ifaptmp->ifa_name, ifaptmp2->ifa_name, sizeof ifaptmp->ifa_name) && ifaptmp2->ifa_addr->sa_family == AF_PACKET)
                        {
                            printf("Found available interface: %s\n", ifaptmp->ifa_name);

                            struct sockaddr_ll *sll = (struct sockaddr_ll *)ifaptmp2->ifa_addr;
                            main->indexInterface = sll->sll_ifindex;
                            freeifaddrs(ifap);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    freeifaddrs(ifap);
    printf("%s: Unknowm host: %s\n", PROGRAM, sourceCount >= targetCount ? main->targetIp : main->sourceIp);
    return -1;
}