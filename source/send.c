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

            if (position % 2 == 0) {
                adresse[octet] = valeur << 4;
            }
            else {
                adresse[octet] |= valeur;
            }

            position++;
        }
    }
}

// void toIP(const char* adresseIP, unsigned char* adresse)
// {
//     int valeur = 0;
//     int octet = 0;
//     int position = 0;

//     for (int i = 0; i < strlen(adresseIP); i++) {
//         if (adresseIP[i] == '.') {
//             adresse[octet] = (unsigned char)valeur;
//             valeur = 0;
//             octet++;
//         }
//         else if (adresseIP[i] >= '0' && adresseIP[i] <= '9') {
//             valeur = valeur * 10 + (adresseIP[i] - '0');
//         }
//         else {
//             // Gérer les erreurs de format d'adresse IP ici
//             return;
//         }
//     }

//     adresse[octet] = (unsigned char)valeur;
// }


int sendArpReply(t_main *main)
{
    unsigned char buffer[sizeof(struct ethhdr) + sizeof(struct arphdr) + 20];
    struct ethhdr* ethHeader;
    struct arphdr* arpHeader;
    struct sockaddr_in target;
	in_addr_t targetIp = inet_addr(main->targetIp);
	in_addr_t sourceIp = inet_addr(main->sourceIp);
	unsigned char sourceMac[6];
	unsigned char targetMac[6];

	toMAC(main->sourceMac, sourceMac);
	toMAC(main->targetMac, targetMac);

    ft_memset(&buffer, 0, sizeof buffer);
    ft_memset(&target, 0, sizeof target);

    target.sin_family = AF_PACKET;
    target.sin_addr.s_addr = targetIp;

    ethHeader = (struct ethhdr *)buffer;
    ethHeader->h_proto = htons(ETH_P_ARP);
    ft_memcpy(ethHeader->h_source, &sourceMac, 6);
    ft_memcpy(ethHeader->h_dest, &targetMac, 6);

    arpHeader = (struct arphdr *)(buffer + sizeof(struct ethhdr));
    arpHeader->ar_hrd = htons(ARPHRD_ETHER);
    arpHeader->ar_pro = htons(ETH_P_IP);
    arpHeader->ar_op = htons(ARPOP_REPLY);
    arpHeader->ar_hln = 6;
    arpHeader->ar_pln = 4;

    unsigned char *adress = buffer + sizeof(struct ethhdr) + sizeof(struct arphdr);

    ft_memcpy(adress, &sourceMac, 6);
    ft_memcpy(adress + arpHeader->ar_pln, &sourceIp, 4);
    ft_memcpy(adress + arpHeader->ar_hln, &targetMac, 6);
    ft_memcpy(adress + arpHeader->ar_pln, &targetIp, 4);

    printf("Now sending an ARP reply to the target address with spoofed source, please wait... \n");
    
    // ssize_t packetSize = sendto(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&target, sizeof(target)); // mettre le destinataire
    // if (packetSize < 0) 
    // {
    //     fprintf(stderr, "%s: sendto failed: %s\n", PROGRAM, strerror(errno));
    //     return -1;
    // }
	printf("Sent an ARP reply packet, you may now check the arp table on the target \n");
    return 0;
}