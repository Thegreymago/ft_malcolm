#include "../includes/ft_malcolm.h"

void handleCtrlC(int sig) {
    printf("\n%s: SIGINT received. Stopping the program.\n", PROGRAM);
    if (sig == SIGINT)
    {
        close(sockfd);
        sockfd = -1;
    }
    return;
}