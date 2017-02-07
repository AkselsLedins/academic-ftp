/*
** exec.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:34:39 2014 ledins
** Last update Sun Apr 13 18:40:07 2014 ledins
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "ftp.h"

char *extract_path(char *opt)
{
  int ii;
  int kk;
  char *result;

  ii = 0;
  while (opt && opt[ii] != '\t' && opt[ii] != ' ' && opt[ii] != '\0')
    ii++;
  while (opt[ii] == ' ' || opt[ii] == '\t')
    ii++;
  kk = ii;
  while (opt[ii] != ' ' && opt[ii] != '\0' && opt[ii] != '\t')
    ii++;
  if (!(ii - kk))
    return (NULL);
  result = malloc(sizeof(char) * (ii - kk + 1));
  if (result == NULL)
    exit(EXIT_FAILURE);
  ii = 0;
  while (opt[kk] != ' ' && opt[kk] != '\0' && opt[kk] != '\t')
    result[ii++] = opt[kk++];
  result[ii] = '\0';
  return (result);
}

char *delete_n_first_char(char *str, size_t n)
{
  str = str + n;
  return (str);
}

char *cd_fix_repo(char *repo)
{
  if (!repo)
    return (NULL);
  if (strlen(repo) == 0)
    return (strdup("/"));
  return (repo);
}

char *extract_file_name(char *opt)
{
  while (opt && (opt[0] != ' ' && opt[0] != '\t'))
    opt = opt + 1;
  while (opt && (opt[0] == ' ' || opt[0] == '\t'))
    opt = opt + 1;
  return (opt);
}

void transmit_file(t_cli *cli, FILE *fd)
{
  char buf[250];
  char *line;
  int size;
  size_t len;
  ssize_t read;
  int totalsize;

  len = 0;
  line = NULL;
  bzero(buf, 250);
  size = filesize(fd);
  sprintf(buf, ".info %d\n", size);
  ftp_send(cli->socket, buf , strlen(buf));
  totalsize = 0;
  while ((read = getline(&line, &len, fd)) != -1)
    {
      usleep(200);
      totalsize += ftp_send(cli->socket, line , strlen(line));
      bzero(buf, 250);
      ftp_recv(cli->socket, buf, sizeof(buf));
      free(line);
      line = NULL;
    }
  totalsize += ftp_send(cli->socket, "\n" , 1);
}
