#include "../includes/ft_malcolm.h"


void display_network_interface(struct ifaddrs* ifap)
{
	printf("Network interface available :\n");
	for (struct ifaddrs* ifaptmp = ifap; ifaptmp != NULL; ifaptmp = ifaptmp->ifa_next)
	{
		printf("Name: %s\n", ifaptmp->ifa_name);
		// printf("Address: %\n", ifaptmp->ifa_name);
	}
	
}