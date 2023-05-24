#include "../includes/ft_malcolm.h"


void display_network_interface(struct ifaddrs* ifap)
{
	printf("Network interface available :\n");
	for (struct ifaddrs* ifaptmp = ifap; ifaptmp != NULL; ifaptmp = ifaptmp->ifa_next)
	{
		printf("Name: %s", ifaptmp->ifa_name);
		if (ifaptmp->ifa_addr->sa_family == AF_INET)
			printf("	Ipv4\n");
		else if (ifaptmp->ifa_addr->sa_family == AF_PACKET)
			printf("	PACKET\n");
		if (ifaptmp->ifa_addr->sa_family == AF_INET6)
			printf("	Ipv6\n");
		else
			printf("\n");
	}
	
}