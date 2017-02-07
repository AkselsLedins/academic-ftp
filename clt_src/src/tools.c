/*
** tools.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:54:02 2014 ledins
** Last update Sun Apr 13 15:54:05 2014 ledins
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"

int usage(char *prog)
{
  fprintf(stderr, "Usage ./%s ip port\n", prog);
  return (FTP_FAILURE);
}

ssize_t ftp_send(int sockfd, const void *buf, size_t len)
{
  return (write(sockfd, buf, len));
}

ssize_t ftp_recv(int sockfd, void *buf, size_t len)
{
  return (read(sockfd, buf, len));
}

char *delete_first_spaces(char *raw)
{
  while (raw && (raw[0] == ' ' || raw[0] == '\t'))
    raw = raw + 1;
  return (raw);
}

void tej_retourchariot(char *buf)
{
  int i;

  i = 0;
  while (buf && buf[i])
    {
      if (buf[i] == '\n' || buf[i] == '\r')
	buf[i] = '\0';
      i++;
    }
}
