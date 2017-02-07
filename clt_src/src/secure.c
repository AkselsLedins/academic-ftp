/*
** secure.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:53:33 2014 ledins
** Last update Sun Apr 13 15:53:35 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include "ftp.h"

void send_magic_number(t_network *n)
{
  char buf[1024];

  ftp_send(n->socket, n->magicNumber, strlen(n->magicNumber));
  ftp_recv(n->socket, buf, sizeof(buf));
  printf("%s%s%s", COLOR_Y, buf, COLOR_DEFAULT);
}
