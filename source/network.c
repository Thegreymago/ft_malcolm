#include "../includes/ft_malcolm.h"

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