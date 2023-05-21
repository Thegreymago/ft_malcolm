#include "../includes/ft_malcolm.h"

void handleCtrlC(int sig) {
    printf("Signal CTRL+C reçu. Arrêt du programme.\n");
    (void)sig;
    // Ajoutez ici le code pour effectuer des opérations de nettoyage ou de gestion avant de quitter le programme
    return;
}