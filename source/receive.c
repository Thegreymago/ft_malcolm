#include "../includes/ft_malcolm.h"


int receiveArpRequest(t_main *main)
{
    unsigned char buffer[sizeof (struct ethhdr) + sizeof (struct arphdr) + 20]; // 20 = 6+6+4+4
    struct sockaddr_ll sender;
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;

    ft_memset(&buffer, 0, sizeof buffer);
    ft_memset(&sender, 0, sizeof sender);
    sender.sll_family = AF_PACKET;
    sender.sll_protocol = htons(ETH_P_ARP);
    sender.sll_ifindex = main->indexInterface;
    socklen_t len = sizeof(sender);

    while (1)
    {
        ssize_t packetSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender, &len);
        if (packetSize < 0) 
        {
            fprintf(stderr, "%s: recvfrom failed: %s\n", PROGRAM, strerror(errno));
            return -1;
        }
        ethHeader = (struct ethhdr*)buffer;
		
        if (ntohs(ethHeader->h_proto) == ETH_P_ARP)
        {
            arpHeader = (struct arphdr*)(buffer + sizeof(struct ethhdr));
            
            if (ntohs(arpHeader->ar_op) == ARPOP_REQUEST)
            {
                printf("[ -- -- An ARP request has been broadcast -- -- ]\n");

                // unsigned char* sourceMACeth = ethHeader->h_source;
                // unsigned char* destMACeth = ethHeader->h_dest;

                unsigned char* sourceMAC = (unsigned char*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
                unsigned char* senderIP = sourceMAC + arpHeader->ar_hln;
                // unsigned char* destMAC = senderIP + arpHeader->ar_pln;
                // unsigned char* targetIP = destMAC + arpHeader->ar_hln;

                // printf("- ETH Adresse MAC source: %02x:%02x:%02x:%02x:%02x:%02x\n", sourceMACeth[0], sourceMACeth[1], sourceMACeth[2], sourceMACeth[3], sourceMACeth[4], sourceMACeth[5]);
                // printf("- ETH Adresse MAC destination: %02x:%02x:%02x:%02x:%02x:%02x\n\n", destMACeth[0], destMACeth[1], destMACeth[2], destMACeth[3], destMACeth[4], destMACeth[5]);

                printf("- Adresse MAC source: %02x:%02x:%02x:%02x:%02x:%02x\n", sourceMAC[0], sourceMAC[1], sourceMAC[2], sourceMAC[3], sourceMAC[4], sourceMAC[5]);
                printf("- Adresse IP source: %d.%d.%d.%d\n\n", senderIP[0], senderIP[1], senderIP[2], senderIP[3]);
                // printf("- Adresse MAC destination: %02x:%02x:%02x:%02x:%02x:%02x\n", destMAC[0], destMAC[1], destMAC[2], destMAC[3], destMAC[4], destMAC[5]);
                // printf("- Adresse IP destination: %d.%d.%d.%d\n\n", targetIP[0], targetIP[1], targetIP[2], targetIP[3]);

				break ;
            }
        }
    }
    return 0;
}