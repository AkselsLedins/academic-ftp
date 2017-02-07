/*
** network.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 15:52:22 2014 ledins
** Last update Sun Apr 13 16:00:40 2014 ledins
*/

#include <arpa/inet.h>
#include <stdio.h>
#include "ftp.h"

void ftp_socket(t_network *network)
{
  network->protocole = getprotobyname("TCP");
  network->socket = socket(AF_INET, SOCK_STREAM, network->protocole->p_proto);

  if (network->socket == FTP_FAILURE)
    {
      perror("[Error] socket failed");
      free(network);
      exit(EXIT_FAILURE);
    }
}

void ftp_close(t_network *network)
{
  close(network->socket);
  free(network);
}

void ftp_connect(t_network *network)
{
  int error;

  network->sin.sin_family = AF_INET;
  network->sin.sin_port = htons(network->port);
  network->sin.sin_addr.s_addr = inet_addr(network->ip);
  error = connect(network->socket,
		  (const struct sockaddr *)&network->sin,
		  sizeof(network->sin));
  if (error == -1)
    {
      ftp_close(network);
      printf("Connect failed\n");
      exit(EXIT_FAILURE);
    }
}
