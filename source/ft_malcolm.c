#include "../includes/ft_malcolm.h"

int ft_malcolm(int argc, char **argv)
{
    int sockfd;
    unsigned char buffer[BUFFER_SIZE];
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;
    
    if (handleErrorInput(argc, argv) == -1)
        return 1;
    
    if (getNetworkInterface() == -1)
        return 1;
    
    // Création du socket brut
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }
}