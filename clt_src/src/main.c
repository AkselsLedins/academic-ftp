/*
** main.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:52:00 2014 ledins
** Last update Sun Apr 13 15:52:04 2014 ledins
*/

#include <stdlib.h>
#include "ftp.h"

int main(int argc, char **argv)
{
t_network *network;

network = NULL;
network = init_network(network, argc, argv);
if (!network)
  return (EXIT_SUCCESS);
ftp_socket(network);
ftp_connect(network);
send_magic_number(network);
ftp_run(network);
ftp_close(network);
return (EXIT_SUCCESS);
}
