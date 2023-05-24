#include "../includes/ft_malcolm.h"

int sameNetwork(uint32_t ip1, uint32_t ip2, uint32_t mask) {
    return (ip1 & mask) == (ip2 & mask);
}

int getNetworkInterface(t_main *main)
{
    struct ifaddrs *ifap = NULL;

    if (getifaddrs(&ifap) == -1)
    {
        fprintf(stderr, "%s: getifaddrs failed: %s\n", PROGRAM, strerror(errno));
        freeifaddrs(ifap);
        return -1;
    }
    // display_network_interface(ifap);

    for (struct ifaddrs *ifaptmp = ifap; ifaptmp; ifaptmp = ifaptmp->ifa_next)
    {
        if (ifaptmp && ifaptmp->ifa_addr && ifaptmp->ifa_netmask && ifaptmp->ifa_addr->sa_family == AF_INET)
        {
            uint32_t networkIP = ((struct sockaddr_in *)ifaptmp->ifa_addr)->sin_addr.s_addr;
            uint32_t networkMask = ((struct sockaddr_in *)ifaptmp->ifa_netmask)->sin_addr.s_addr;

            // char ip[INET6_ADDRSTRLEN];
            // struct sockaddr_in* addr_in = (struct sockaddr_in*)ifaptmp->ifa_addr;
            // inet_ntop(AF_INET, &(addr_in->sin_addr), ip, INET_ADDRSTRLEN);
            // printf("NetworkIP address: %s\n", ip);

            // printf("MachineIP 1: %d | MachineIP 2: %d\n", main->sourceIp, main->targetIp);
            // printf("NetworkIP: %d | Mask: %d\n", networkIP, networkMask);
            // printf(" Cmp1: %d | Cmp2: %d\n", sameNetwork(networkIP, main->sourceIp, networkMask), sameNetwork(networkIP, main->targetIp, networkMask));
            
            
            if (sameNetwork(networkIP, main->sourceIp, networkMask) && sameNetwork(networkIP, main->targetIp, networkMask))
            {
                for (struct ifaddrs *ifaptmp2 = ifap; ifaptmp2; ifaptmp2 = ifaptmp2->ifa_next)
                {
                    if (ifaptmp2 && !ft_memcmp(ifaptmp->ifa_name, ifaptmp2->ifa_name, sizeof ifaptmp->ifa_name) && ifaptmp2->ifa_addr->sa_family == AF_PACKET)
                    {
                        printf("Found available interface: %s\n", ifaptmp->ifa_name);
                        ft_strlcpy(main->interfaceName, ifaptmp->ifa_name, ft_strlen(ifaptmp->ifa_name));
                        freeifaddrs(ifap);
                        return 1;
                    }
                }
            }
        }
    }
    freeifaddrs(ifap);
    printf("%s: Unknowm host\n", PROGRAM); // ajouter le probleme de l'adresse
    return 0;
}