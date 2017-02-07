/*
** get.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 15:51:37 2014 ledins
** Last update Sun Apr 13 16:00:22 2014 ledins
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

static void get_file_name(char *raw, char *cmd)
{
  int i;
  int k;

  i = 0;
  k = 0;
  while (raw && (raw[i] == ' ' || raw[i] == '\t'))
    i++;
  while (raw && raw[i] != '\0' &&
	 raw[i] != ' ' && raw[i] != '\t' && k < 40)
    i++;
  while (raw && (raw[i] == ' ' || raw[i] == '\t'))
    i++;
  while (raw && raw[i] != ' ' && raw[i] != '\t'
	 && raw[i] != '\0'&& k < 40)
    {
      cmd[k] = raw[i];
      k++;
      i++;
    }
  cmd[k] = '\0';
}

static int get_size_file(t_network *network)
{
  char buf[200];
  char size[200];
  int i;
  int k;

  k = 0;
  i = 5;
  bzero(size, sizeof(buf));
  bzero(buf, sizeof(buf));
  ftp_recv(network->socket, buf, sizeof(buf));
  if (strncmp(buf, ".info", 5) != 0)
    {
      printf("%s%s%s", COLOR_Y, buf, COLOR_DEFAULT);
      return (-1);
    }
  while (buf[i] != '\0')
    {
      size[k] = buf[i];
      i++;
      k++;
    }
  return (atoi(size));
}

int exec_get(t_network *network, char *cmd)
{
  char file_name[128];
  char buf[200];
  int nread;
  int finalsize;
  int current_size;
  int new_file_fd;

  bzero(file_name, 128);
  get_file_name(cmd, file_name);
  if ((finalsize = get_size_file(network)) == -1)
    return (-1);
  current_size = 0;
  bzero(buf, sizeof(buf));
  if ((new_file_fd = open(file_name, O_RDWR | O_CREAT, 0666)) == -1)
    perror("");
  while ((nread = read(network->socket, buf, sizeof(buf))) > 0
	 && current_size < finalsize)
    {
      current_size += (int)nread;
      if (new_file_fd != -1)
	write(new_file_fd, buf, strlen(buf));
      ftp_send(network->socket, "OK\n", 3);
      bzero(buf, sizeof(buf));
    }
  return (0);
}
