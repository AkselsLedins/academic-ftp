/*
** secure.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cli
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 19:01:53 2014 ledins
** Last update Sun Apr 13 19:01:59 2014 ledins
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "ftp.h"

void authenticate_user_acreat(t_cli *cli)
{
  cli->authenticated = TRUE;
  ftp_send(cli->socket,
	   "[Server] Account created, you are logged in !\n", 46);
}

void try_magic_number(t_network *network, t_cli *cli)
{
  char buf[LEN_BUFFER];
  ssize_t n;

  bzero(buf, LEN_BUFFER);
  n = ftp_recv(cli->socket, buf, LEN_BUFFER - 1);
  buf[n] = '\0';
  if (!is_integer(buf))
    {
      ftp_send(cli->socket, "[Server] Connexion Refused: Not a compatible"\
	       " client\n", 52);
      free(cli);
      exit(EXIT_FAILURE);
    }
  if (atoi(buf) == network->magicNumber)
    {
      ftp_send(cli->socket, "[Server] Connexion etablished..\n", 32);
      return;
    }
  ftp_send(cli->socket, "[Server] Connexion Refused: Not a compatible"\
	   " client\n", 52);
  free(cli);
  exit(EXIT_FAILURE);
}
