/*
** ftp.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:51:19 2014 ledins
** Last update Sun Apr 13 21:01:08 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include "ftp.h"

static void prompt(t_network *network)
{
  printf("ftp@%s:%d  >  ", network->ip, network->port);
  fflush(stdout);
}

static void ftp_retexec(t_network *network)
{
  char buf[1024];

  bzero(buf, sizeof(buf));
  ftp_recv(network->socket, buf, sizeof(buf));
  printf("%s%s%s", COLOR_Y, buf, COLOR_DEFAULT);
}

void ftp_run(t_network *network)
{
  char buf[1024];
  int ret;
  int cmd;

  bzero(buf, sizeof(buf));
  prompt(network);
  while ((ret = read(0, buf, sizeof(buf))) > 0)
    {
      cmd = parsing_cmd(buf);
      ret = 0;
      ftp_send(network->socket, buf, strlen(buf));
      if (cmd == CMD_PUT)
	ret = exec_put(network, buf);
      if (cmd == CMD_GET)
	ret = exec_get(network, buf);
      else if (cmd == CMD_QUIT)
	return;
      bzero(buf, sizeof(buf));
      if (!ret)
	  ftp_retexec(network);
      prompt(network);
      bzero(buf, sizeof(buf));
    }
}
