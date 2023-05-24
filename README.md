# ft_malcolm
MITM

TODO :


memcpy
memset
memcmp

Lien utiles :

RFC 826 : https://www.ietf.org/rfc/rfc826.txt  
RFC 7042 : https://datatracker.ietf.org/doc/html/rfc7042  
Socket ARP REQUEST : https://stackoverflow.com/questions/16710040/arp-request-and-reply-using-c-socket-programming  
https://www.it-connect.fr/comprendre-les-attaques-via-arp-spoofing-mitm-dos/  
https://www.pdbuchan.com/rawsock/arp.c


 Voici les spécifications demandées :

Votre programme doit pouvoir être arrêté lorsque l'utilisateur appuie sur Ctrl+C.
Le programme doit prendre quatre arguments dans l'ordre suivant :
IP source
Adresse MAC source
IP cible
Adresse MAC cible

Lorsque le programme est lancé, il doit attendre une demande ARP (Address Resolution Protocol) émise en diffusion par la cible, demandant l'IP source. Ensuite, votre programme doit envoyer une seule réponse ARP à la cible, puis se terminer. Si tout se passe bien, la table ARP de la cible devrait contenir l'association IP et MAC que vous avez fournie en tant que source.

Exemple d'utilisation basique :

./ft_malcolm 10.12.255.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:b1:**:**:**

Le programme envoie une réponse ARP à la cible (10.12.10.22) contenant les informations sur la source (10.12.255.255 et son adresse MAC associée, falsifiée) dès qu'il détecte qu'une demande ARP a été envoyée sur le réseau.

Le sujet mentionne également quelques exemples de gestion des erreurs possibles, comme des adresses IP ou MAC invalides.

Il est important de noter que le spoofing d'adresses IP appartenant à d'autres personnes peut entraîner des problèmes et/ou des sanctions. Vous n'êtes autorisé à falsifier que vos propres adresses IP, par exemple celles de votre machine virtuelle.


Pour commencer, vous pouvez suivre ces étapes pour réaliser votre projet :

- Familiarisez-vous avec le protocole ARP (Address Resolution Protocol) et comprenez son fonctionnement, notamment la demande ARP et la réponse ARP.
- Apprenez les bases de la programmation réseau et des sockets en utilisant le langage de programmation de votre choix.
- Créez un nouveau projet et définissez la structure de votre programme, en tenant compte des exigences spécifiées dans le sujet.
- Implémentez la logique de capture de la demande ARP envoyée en diffusion par la cible. Vous pouvez utiliser des bibliothèques ou des API fournies par votre langage de programmation pour effectuer cette capture.
Une fois la demande ARP capturée, analysez-la pour extraire les informations pertinentes, telles que l'adresse IP source de la cible.
- Générez une réponse ARP en utilisant les informations fournies en tant qu'arguments, en remplissant correctement les champs de l'en-tête ARP.
- Envoyez la réponse ARP à la cible en utilisant les sockets réseau appropriés. Assurez-vous que la réponse est bien formée et conforme au protocole ARP.
- Vérifiez que la réponse ARP a été correctement envoyée en vous assurant que les informations de la table ARP de la cible sont mises à jour avec les valeurs que vous avez fournies en tant que source.
- Implémentez la gestion de l'interruption par Ctrl+C afin que votre programme puisse être arrêté proprement lorsque l'utilisateur le souhaite.
- Testez votre programme en exécutant différentes configurations et en vérifiant les résultats.

N'oubliez pas de documenter votre code et d'ajouter des commentaires pour expliquer les différentes parties de votre programme.


Fonctions autorisées :

- sendto: 
Cette fonction est utilisée pour envoyer des données sur un socket spécifié vers une adresse de destination spécifiée.
- recvfrom: 
Cette fonction est utilisée pour recevoir des données à partir d'un socket spécifié et obtenir l'adresse source des données reçues.
- socket: 
Cette fonction crée un nouveau socket et retourne son descripteur. Le socket peut être utilisé pour la communication réseau.
- setsockopt: 
Cette fonction permet de définir des options pour un socket, comme la réutilisation de l'adresse ou l'activation du mode non-blocant.
- getuid: 
Cette fonction renvoie l'ID utilisateur effectif du processus en cours.
- close: 
Cette fonction ferme le descripteur de fichier spécifié, y compris un socket.
- signal: 
Cette fonction permet de gérer les signaux logiciels, tels que SIGINT pour capturer le signal de terminaison Ctrl+C.
- inet_addr: 
Cette fonction convertit une adresse IPv4 au format texte en une représentation numérique sous forme binaire utilisée par le réseau.
- gethostbyname: 
Cette fonction renvoie une structure d'informations sur un hôte (nom d'hôte) en utilisant son nom.
- getaddrinfo, freeaddrinfo: 
Ces fonctions permettent de résoudre un nom d'hôte en une liste d'adresses IP utilisables. freeaddrinfo est utilisé pour libérer la mémoire allouée par getaddrinfo.
- getifaddrs, freeifaddrs: 
Ces fonctions permettent de récupérer la liste des interfaces réseau disponibles sur le système. freeifaddrs est utilisé pour libérer la mémoire allouée par getifaddrs.
- htons, ntohs: 
Ces fonctions permettent de convertir les valeurs d'entiers courts de l'ordre d'octets de l'hôte à l'ordre d'octets du réseau (et vice versa) pour la gestion des numéros de port.
- strerror, gai_strerror: 
Ces fonctions renvoient une chaîne de caractères décrivant le message d'erreur associé à un code d'erreur spécifié. strerror est utilisé pour les erreurs système générales, tandis que gai_strerror est utilisé pour les erreurs liées à getaddrinfo.
- printf et sa famille: 
Ce sont des fonctions de sortie formatée permettant d'afficher des données formatées sur la sortie standard. D'autres variantes, telles que fprintf et sprintf, permettent de formater les données dans une chaîne de caractères ou un fichier spécifié.


Verification :
- Check les leaks memoire
- Check les leaks FD


Interface reseaux aptes :
- "eth" ou "enp" (pour le filaire)
- "wlan" ou "wlp" (pour le WiFi)

struct ifaddrs {
	struct ifaddrs  *ifa_next;    /* Next item in list */
	char            *ifa_name;    /* Name of interface */
	unsigned int     ifa_flags;   /* Flags from SIOCGIFFLAGS */
	struct sockaddr *ifa_addr;    /* Address of interface */
	struct sockaddr *ifa_netmask; /* Netmask of interface */
	union {
		struct sockaddr *ifu_broadaddr;
						/* Broadcast address of interface */
		struct sockaddr *ifu_dstaddr;
						/* Point-to-point destination address */
	} ifa_ifu;
#define              ifa_broadaddr ifa_ifu.ifu_broadaddr
#define              ifa_dstaddr   ifa_ifu.ifu_dstaddr
	void            *ifa_data;    /* Address-specific data */
};

struct sockaddr_in {
	short   sin_family;
	u_short sin_port;
	struct  in_addr sin_addr;
	char    sin_zero[8];
};

struct in_addr {
    uint32_t       s_addr;     /* Adresse dans l'ordre d'octets réseau */
};


sudo valgrind ./ft_malcolm 192.168.1.255 ff:bb:ff:ff:ee:ff 192.168.1.23 10:dd:b1:ff:ff:ff
