/*
** network.c for ftp_serveur in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:36:01 2014 ledins
** Last update Sun Apr 13 18:45:38 2014 ledins
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/tcp.h>
#include "ftp.h"

void ftp_socket(t_network *network)
{
  network->socket = socket(AF_INET, SOCK_STREAM, network->protocole->p_proto);
  if (network->socket == FTP_FAILURE)
    {
      perror("[Error] socket failed");
      free(network);
      exit(EXIT_FAILURE);
    }
}

void ftp_bind(t_network *network)
{
  int rbind;

  network->sin.sin_family = AF_INET;
  network->sin.sin_port = htons(network->port);
  network->sin.sin_addr.s_addr = INADDR_ANY;
  rbind = bind(network->socket, (const struct sockaddr *)&(network->sin),
	       sizeof(network->sin));
  if (rbind == FTP_FAILURE)
    {
      perror("[Error] bind failed");
      ftp_close(network);
      exit(EXIT_FAILURE);
    }
}

void ftp_reuseaddr(t_network *network)
{
  int whyNot;
  int ret;

  whyNot = 1;
  ret = setsockopt(network->socket,
		   SOL_SOCKET,
		   SO_REUSEADDR,
		   &whyNot, sizeof(int));
  if (ret == FTP_FAILURE)
    {
      perror("[Error] setsockopt");
      ftp_close(network);
      exit(EXIT_FAILURE);
    }
}

void ftp_close(t_network *network)
{
  close(network->socket);
  free(network);
}

void ftp_listen(t_network *network)
{
  int rlisten;

  printf("Waiting for connexions...\n");
  rlisten = listen(network->socket, network->queue);
  if (rlisten <= FTP_FAILURE)
    {
      perror("[Error] listen failed");
      ftp_close(network);
      exit(EXIT_FAILURE);
    }
}
