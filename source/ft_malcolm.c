#include "../includes/ft_malcolm.h"

int receiveArpRequest(t_main *main)
{
    (void)main; // DEPEND DE COMMENT JE SET LA CONNEXION A L'INTERFACE
    unsigned char buffer[sizeof (struct ethhdr) + sizeof (struct arphdr)];
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;

    ft_memset(&buffer, 0, sizeof buffer);

    while (1) 
    {
        ssize_t packetSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
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
                printf("An ARP request has been broadcast\n");

                unsigned char* targetIP = (unsigned char*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
                unsigned char* senderIP = targetIP + arpHeader->ar_pln;
                unsigned char* sourceMAC = ethHeader->h_source;
                unsigned char* destMAC = ethHeader->h_dest;
                
                printf("- Adresse IP source: %d.%d.%d.%d\n", senderIP[0], senderIP[1], senderIP[2], senderIP[3]);
                printf("- Adresse MAC source: %02X:%02X:%02X:%02X:%02X:%02X\n", sourceMAC[0], sourceMAC[1], sourceMAC[2], sourceMAC[3], sourceMAC[4], sourceMAC[5]);
                printf("- Adresse IP destination: %d.%d.%d.%d\n", targetIP[0], targetIP[1], targetIP[2], targetIP[3]);
                printf("- Adresse MAC destination: %02X:%02X:%02X:%02X:%02X:%02X\n\n", destMAC[0], destMAC[1], destMAC[2], destMAC[3], destMAC[4], destMAC[5]);
            }
        }
    }
    return 0;
}

int setData(t_main *main, char **argv)
{
    
    ft_memset(&main->interfaceName, 0, sizeof(main->interfaceName));
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
    {
        fprintf(stderr, "%s: socket failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

    // struct ifreq ifr;

    // ft_memset(&ifr, 0, sizeof(ifr));
    // ft_strlcpy(ifr.ifr_name, main->interfaceName, IFNAMSIZ - 1);
    // if (setsockopt(sockfd, SOL_PACKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) == -1)
    // {
    //     fprintf(stderr, "%s: setsockopt failed: %s\n", PROGRAM, strerror(errno));
    //     return -1;
    // }

    main->sourceIp = inet_addr(argv[1]);
    main->sourceMac = inet_addr(argv[2]);
    main->targetIp = inet_addr(argv[3]);
    main->targetMac = inet_addr(argv[4]);


    return 0;
}

int sendArpReply(t_main *main)
{
    (void)main;
    unsigned char buffer[sizeof (struct ethhdr) + sizeof (struct arphdr)];
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;

    ft_memset(&buffer, 0, sizeof buffer);

    ethHeader = (struct ethhdr *)buffer;
    ethHeader->h_proto = htons(ETH_P_ARP);
    ft_memcpy(&main->sourceMac, ethHeader->h_source, sizeof (uint32_t));
    ft_memcpy(&main->targetMac, ethHeader->h_dest, sizeof (uint32_t));

    arpHeader = (struct arphdr *)(buffer + sizeof(struct ethhdr));

    ssize_t packetSize = sendto(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL); // mettre le destinataire
    if (packetSize < 0) 
    {
        fprintf(stderr, "%s: sendto failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

    return 0;
}




int ft_malcolm(int argc, char **argv)
{
    t_main  main;

    // printf("taille ethhdr = %ld octets soit %ld bits\n", sizeof(struct ethhdr), sizeof(struct ethhdr) * 8);
    // printf("taille arphdr = %ld octets soit %ld bits\n", sizeof(struct arphdr), sizeof(struct arphdr) * 8);
    // printf("taille sockaddr_in = %ld octets soit %ld bits\n\n", sizeof(struct sockaddr_in), sizeof(struct sockaddr_in) * 8);

    signal(SIGINT, handleCtrlC);

    if (handleErrorInput(argc, argv) == -1)
        return (close(sockfd), -1);

    if (setData(&main, argv) == -1)
        return (close(sockfd), -1);
    
    if (getNetworkInterface(&main) == -1)
        return (close(sockfd), -1);

    if (receiveArpRequest(&main) == -1)
        return (close(sockfd), -1);

    if (sendArpReply(&main) == -1)
        return (close(sockfd), -1);
    close(sockfd);
    return 0;
}