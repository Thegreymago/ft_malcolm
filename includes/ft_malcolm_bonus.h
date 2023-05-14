#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* Inclusion des dépendances */

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"


/* Définition des constantes */

# define ARG "Error\nIncorrect number of arguments\n"


/* Déclaration des structures */

typedef struct s_main
{
	int		scr_y;
	int		scr_x;
	int		c;
	int		f;
	t_data	*game;
	t_xpm	*img;
	t_xpm	*texture;
	t_ray	*ray;
	t_map	*c_map;
	t_tex	*tex;
}	t_main;

/* Prototype des fonctions */

#endif