

void handleCtrlC(int sig) {
    printf("Signal CTRL+C reçu. Arrêt du programme.\n");
    // Ajoutez ici le code pour effectuer des opérations de nettoyage ou de gestion avant de quitter le programme
    exit(EXIT_SUCCESS);
}