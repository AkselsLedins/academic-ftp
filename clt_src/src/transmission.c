/*
** transmission.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:54:18 2014 ledins
** Last update Sun Apr 13 15:54:27 2014 ledins
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

int filesize(FILE *fp)
{
  int sz;

  fseek(fp, 0L, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  return (sz);
}

void transmit_file(t_network *network, FILE *fd)
{
  int totalsize;
  int size;
  size_t len;
  ssize_t read;
  char buf[250];
  char *line;

  totalsize = 0;
  size = filesize(fd);
  sprintf(buf, ".info %d\n", size);
  ftp_send(network->socket, buf , strlen(buf));
  while ((read = getline(&line, &len, fd)) != -1)
    {
      usleep(200);
      totalsize += ftp_send(network->socket, line , strlen(line));
      bzero(buf, 250);
      ftp_recv(network->socket, buf, sizeof(buf));
      free(line);
      line = NULL;
    }
  totalsize += ftp_send(network->socket, "\n" , 1);
}

int ftp_check_file(char *path)
{
  int status;
  struct stat st_buf;

  status = stat(path, &st_buf);
  if (status != 0)
    {
      fprintf(stderr, "file at %s does not exists\n", path);
      return (-1);
    }
  if (S_ISDIR (st_buf.st_mode))
    {
      fprintf(stderr, "file requested is a directory\n");
      return (-1);
    }
  return (0);
}
