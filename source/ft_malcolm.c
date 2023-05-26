#include "../includes/ft_malcolm.h"

int setData(t_main *main, char **argv)
{
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
    {
        fprintf(stderr, "%s: socket failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

    ft_strlcpy(main->sourceIp, argv[1], ft_strlen(argv[1]) + 1);
    ft_strlcpy(main->sourceMac, argv[2], ft_strlen(argv[2]) + 1);
    ft_strlcpy(main->targetIp, argv[3], ft_strlen(argv[3]) + 1);
    ft_strlcpy(main->targetMac, argv[4], ft_strlen(argv[4]) + 1);

    return 0;
}


int ft_malcolm(int argc, char **argv)
{
    t_main  main;

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
    printf("    [Exiting program] \n");
    close(sockfd);
    return 0;
}