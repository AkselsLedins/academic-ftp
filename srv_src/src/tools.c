/*
** tools.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:37:52 2014 ledins
** Last update Sun Apr 13 18:38:02 2014 ledins
*/

#include <ctype.h>
#include <string.h>
#include "ftp.h"

ssize_t ftp_send(int sockfd, const void *buf, size_t len)
{
  return (write(sockfd, buf, len));
}

ssize_t ftp_recv(int sockfd, void *buf, size_t len)
{
  return (read(sockfd, buf, len));
}

int is_integer(char *str)
{
  unsigned int ii;

  ii = 0;
  while (ii < strlen(str))
    {
      if (!isdigit(str[ii]))
	return (FTP_FAILURE);
      ii++;
    }
  return (FTP_SUCCESS);
}

int is_option(char *opt, int flag)
{
  if (opt[1] == flag && opt[0] == '-')
    return (FTP_SUCCESS);
  return (FTP_FAILURE);
}

int filesize(FILE *fp)
{
  int sz;

  fseek(fp, 0L, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  return (sz);
}
