#include "../includes/ft_malcolm.h"


int receiveArpRequest(t_main *main)
{
    unsigned char buffer[BUFFER_SIZE];
    struct sockaddr_ll sender;
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;

    ft_memset(&buffer, 0, sizeof buffer);
    ft_memset(&sender, 0, sizeof sender);

    /* SOCKADDR_LL FOR SENDER NETWORK INTERFACE */
    sender.sll_family = AF_PACKET;
    sender.sll_protocol = htons(ETH_P_ARP);
    sender.sll_ifindex = main->indexInterface;
    socklen_t len = sizeof(sender);

    while (1)
    {
        ssize_t packetSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender, &len);
        if (packetSize < 0)
        {
            if (sockfd == -1)
                return 1;
            fprintf(stderr, "%s: recvfrom failed: %s\n", PROGRAM, strerror(errno));
            return -1;
        }

        /* ETHERNET HEADER */
        ethHeader = (struct ethhdr*)buffer;
		
        if (ntohs(ethHeader->h_proto) == ETH_P_ARP)
        {
            /* ARP HEADER */
            arpHeader = (struct arphdr*)(buffer + sizeof(struct ethhdr));
            
            if (ntohs(arpHeader->ar_op) == ARPOP_REQUEST)
            {
                printf("[ -- -- An ARP request has been broadcast -- -- ]\n");

                unsigned char* sourceMAC = (unsigned char*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
                unsigned char* senderIP = sourceMAC + arpHeader->ar_hln;
                // unsigned char* destMAC = senderIP + arpHeader->ar_pln;
                // unsigned char* targetIP = destMAC + arpHeader->ar_hln;

                printf("- Adresse MAC source: %02x:%02x:%02x:%02x:%02x:%02x\n", sourceMAC[0], sourceMAC[1], sourceMAC[2], sourceMAC[3], sourceMAC[4], sourceMAC[5]);
                printf("- Adresse IP source: %d.%d.%d.%d\n", senderIP[0], senderIP[1], senderIP[2], senderIP[3]);
                // printf("- Adresse MAC target: %02x:%02x:%02x:%02x:%02x:%02x\n", destMAC[0], destMAC[1], destMAC[2], destMAC[3], destMAC[4], destMAC[5]);
                // printf("- Adresse IP target: %d.%d.%d.%d\n\n", targetIP[0], targetIP[1], targetIP[2], targetIP[3]);

				break ;
            }
        }
    }
    return 0;
}