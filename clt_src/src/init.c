/*
** init.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:51:52 2014 ledins
** Last update Sun Apr 13 15:51:55 2014 ledins
*/

#include "ftp.h"

t_network * init_network(t_network *network, int argc, char **argv)
{
if (argc != 3)
  {
usage(argv[0]);
return (NULL);
}
network = malloc(sizeof(t_network));
if (!network)
  return (NULL);
network->ip = argv[1];
network->port = atoi(argv[2]);
network->magicNumber = DEFAULT_MNUM;
return (network);
}
