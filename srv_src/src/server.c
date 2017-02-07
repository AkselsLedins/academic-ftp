/*
** server.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:37:24 2014 ledins
** Last update Sun Apr 13 18:47:27 2014 ledins
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "ftp.h"

int accept_client(t_network *network)
{
  int client_sock;
  socklen_t client_size;

  memset(&network->sin_client, 0, sizeof(network->sin_client));
  client_size = sizeof(network->sin_client);
  client_sock = accept(
		       network->socket,
		       (struct sockaddr *)&(network->sin_client),
		       &client_size);
  if (client_sock == -1)
    {
      perror("[Error] accept");
      return (FTP_FAILURE);
    }
  return (client_sock);
}

void server_start(t_network *network)
{
  int cli_sock;

  while (1)
    {
      cli_sock = accept_client(network);
      if (cli_sock != FTP_FAILURE)
	{
	  printf("Connexion from : %s\n",
		 inet_ntoa(network->sin_client.sin_addr));
	  if (fork() == 0)
	    ftp_cli(network, cli_sock);
	}
    }
}
