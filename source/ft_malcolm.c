#include "../includes/ft_malcolm.h"

int ft_malcolm(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int sockfd;
    unsigned char buffer[BUFFER_SIZE];
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;

    printf("taille ethhdr = %ld octets soit %ld bits\n", sizeof(struct ethhdr), sizeof(struct ethhdr) * 8);
    printf("taille arphdr = %ld octets soit %ld bits\n", sizeof(struct arphdr), sizeof(struct arphdr) * 8);
    printf("taille sockaddr_in = %ld octets soit %ld bits\n\n", sizeof(struct sockaddr_in), sizeof(struct sockaddr_in) * 8);

    if (handleErrorInput(argc, argv) == -1)
        return -1;
    
    if (getNetworkInterface() == -1)
        return -1;

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0)
    {
        fprintf(stderr, "%s: socket failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

    int enable = 1; // interface reseau a mettre
    if (setsockopt(sockfd, SOL_PACKET, SO_BINDTODEVICE, &enable, sizeof(enable)) == -1)
    {
        fprintf(stderr, "%s: setsockopt failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }


    while (1) 
    {
        ssize_t packetSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (packetSize < 0) 
        {
            fprintf(stderr, "%s: recv failed: %s\n", PROGRAM, strerror(errno));
            break;
        }

        ethHeader = (struct ethhdr*)buffer;
        
        if (ntohs(ethHeader->h_proto) == ETH_P_ARP) 
        {
            arpHeader = (struct arphdr*)(buffer + sizeof(struct ethhdr));
            
            if (ntohs(arpHeader->ar_op) == ARPOP_REQUEST)
            {
                
                printf("An ARP request has been broadcast\n");
                
                // Traitement des informations ARP (adresses IP et MAC)
                // ...

                // Exemple d'affichage des adresses IP source et destination
                // struct sockaddr_in* senderIPs = (struct sockaddr_in*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
                // struct sockaddr_in* targetIPs = (struct sockaddr_in*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr) + arpHeader->ar_pln);
                // char senderIPStr[INET_ADDRSTRLEN];
                // char targetIPStr[INET_ADDRSTRLEN];
                
                // inet_ntop(AF_INET, &(senderIPs->sin_addr), senderIPStr, INET_ADDRSTRLEN);
                // inet_ntop(AF_INET, &(targetIPs->sin_addr), targetIPStr, INET_ADDRSTRLEN);
                
                // printf("2: Adresse IP source: %s\n", senderIPStr);
                // printf("2: Adresse IP destination: %s\n", targetIPStr);

                unsigned char* targetIP = (unsigned char*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
                unsigned char* senderIP = targetIP + arpHeader->ar_pln;
                unsigned char* sourceMAC = ethHeader->h_source;
                unsigned char* destMAC = ethHeader->h_dest;
                
                printf("1: Adresse IP source: %hhu.%hhu.%hhu.%hhu\n", senderIP[0], senderIP[1], senderIP[2], senderIP[3]);
                printf("1: Adresse MAC source: %02X:%02X:%02X:%02X:%02X:%02X\n", sourceMAC[0], sourceMAC[1], sourceMAC[2], sourceMAC[3], sourceMAC[4], sourceMAC[5]);
                printf("1: Adresse IP destination: %hhu.%hhu.%hhu.%hhu\n", targetIP[0], targetIP[1], targetIP[2], targetIP[3]);
                printf("1: Adresse MAC destination: %02X:%02X:%02X:%02X:%02X:%02X\n\n", destMAC[0], destMAC[1], destMAC[2], destMAC[3], destMAC[4], destMAC[5]);

            }
        }
    }
    return 0;
}