
/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */
/*                                                                                      */
/*   Nom du fichier : main.c                                                            */
/*      Type du fichier : ASCII text                                                    */
/*                                                                                      */
/*   By: Jo                                                                             */
/*                                                                                      */
/*  Created: 14/05/2023                                                                 */
/*  Updated: 14/05/2023                                                                 */
/*                                                                                      */
/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */

#include "./includes/ft_malcolm.h"

int main (int argc, char **argv)
{
    (void)argc;
    (void)argv;

    //ft_malcolm

    signal(SIGINT, handleCtrlC);
    return 0;
}
