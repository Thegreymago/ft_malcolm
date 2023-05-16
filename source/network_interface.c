#include "../includes/ft_malcolm.h"

void getNetworkInterface()
{
    struct ifaddrs *ifap = NULL;

    if (getifaddrs(&ifap) == -1)
    {
        fprintf(stderr, "getifaddrs failed: %s\n", strerror(errno));
        return 1;
    }
}