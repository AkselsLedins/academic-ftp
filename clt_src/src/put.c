/*
** put.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 15:52:38 2014 ledins
** Last update Sun Apr 13 21:06:05 2014 ledins
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

static int send_file(t_network *network, char *path)
{
  FILE *fd_file;

  if (ftp_check_file(path) == -1)
    return (-1);
  fd_file = fopen(path, "rb");
  if (fd_file)
    {
      transmit_file(network, fd_file);
      fclose(fd_file);
      return (0);
    }
  else
    fprintf(stderr, "put : %s\n", strerror(errno));
  return (-1);
}

static int exec_put_check(t_network *network, char *option)
{
  char buf[PATH_MAX];
  char *new_path;

  bzero(buf, PATH_MAX);
  strcat(buf, option);
  new_path = realpath(buf, NULL);
  if (new_path)
    return (send_file(network, new_path));
  else
    fprintf(stderr, "can't find file %s\n", option);
  return (-1);
}

static char *extract_file_name(char *opt)
{

  while (opt && (opt[0] != ' ' && opt[0] != '\t'))
    opt = opt + 1;
  while (opt && (opt[0] == ' ' || opt[0] == '\t'))
    opt = opt + 1;
  return (opt);
}

static int exec_could_put(t_network *network)
{
  char buf[200];

  bzero(buf, sizeof(buf));
  ftp_recv(network->socket, buf, sizeof(buf));
  if (strncmp(buf, "[Server] waiting transmission", 29) == 0)
    return (0);
  printf("%s%s%s", COLOR_Y, buf, COLOR_DEFAULT);
  return (-1);
}

int exec_put(t_network *network, char *opt)
{
  char *option;

  if (exec_could_put(network) == -1)
    return (-1);
  option = extract_file_name(opt);
  if (option)
    {
      option = strtok(option, "\n");
      option[strlen(option)] = '\0';
      return (exec_put_check(network, option));
    }
  return (-1);
}
