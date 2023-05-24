#include "../includes/ft_malcolm.h"

int checkHexa(char c)
{
    if ((c > 47 && c < 58) || (c > 96 && c < 103) || (c > 64 && c < 71))
		return (1);
	return (0);
}

int checkIp(char *ip)
{
    int i = 0;
    int j = 0;
    int y = 0;
    char *tmp = NULL;
    int byte = 0;
    int nbByte = 0;

    while (ip[i] != '\0')
    {
        j = i;
        y = 0;
        while (ip[j] != '.' && ip[j])
        {
            if (!ft_isdigit(ip[j]))
                return -1;
            ++j;
            ++y;
        }
        if (y > 3 || y == 0)
            return -1;
        ++nbByte;
        tmp = ft_substr(ip, i, y);
        byte = ft_atoi(tmp);
		if (byte == 0 && y != 1)
			return (free(tmp), -1);
        free(tmp);
        if (byte > 255 || byte < 0)
            return -1;
        if (ip[j] == '\0')
            break ;
        else
            i = j + 1;
    }
    if (nbByte != 4)
        return -1;
    return 0;
}

int checkMac(char *mac)
{
    int i = 0;
    int j = 0;
    int y = 0;
    int nbByte = 0;

    while (mac[i])
    {
        j = i;
        y = 0;
        while (mac[j] != ':' && mac[j])
        {
            if (!checkHexa(mac[j]) )
                return -1;
            ++j;
            ++y;
        }
        ++nbByte;
        if (y != 2)
            return -1;
        if (mac[j] == '\0')
            break ;
        else
            i = j + 1;
    }
    if (nbByte != 6)
    	return -1;
    return 0;    
}

int handleErrorInput(int argc, char **argv)
{
    int i = 1;

    if (argc != 5)
    {
        fprintf(stderr, "%s: Incorrect number of arguments\n", PROGRAM);
        return -1;
    }

    while (argv[i])
    {
        if (i % 2 == 1)
        {
            if (checkIp(argv[i]) == -1)
            {
                fprintf(stderr, "%s: Invalid IP adress: %s\n", PROGRAM, argv[i]);
                return -1;
            }
        }
        else
        {
            if (checkMac(argv[i]) == -1)
            {
                fprintf(stderr, "%s: Incorrect MAC adress: %s\n", PROGRAM, argv[i]);
                return -1;
            }
        }
        ++i;
    }



    return 0;
}