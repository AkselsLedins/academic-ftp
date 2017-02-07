/*
** put.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cmds
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 19:54:42 2014 ledins
** Last update Sun Apr 13 21:05:28 2014 ledins
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

static int get_size_file(t_cli *network)
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

static char * transform_file_name(t_cli *cli, char *file)
{
  char buf[PATH_MAX];

  bzero(buf, sizeof(buf));
  strcat(buf, cli->root_dir);
  if (cli->root_dir[strlen(cli->root_dir) - 1] != '/' &&
      cli->current_dir[strlen(cli->current_dir) - 1] != '/')
    strcat(buf, "/");
  strcat(buf, cli->current_dir);
  if (cli->current_dir[strlen(cli->current_dir) - 1] != '/')
    strcat(buf, "/");
  strcat(buf, file);
  return (strdup(buf));
}

void execputs(t_cli *cli, char *file_name, int current_size)
{
  char buf[200];
  int nread;
  int finalsize;
  int new_file_fd;

  if ((finalsize = get_size_file(cli)) != -1)
    {
      bzero(buf, sizeof(buf));
      new_file_fd = open(file_name, O_RDWR | O_CREAT, 0666);
      if (new_file_fd == -1)
	perror("");
      while ((nread = read(cli->socket, buf, sizeof(buf))) > 0
	     && current_size < finalsize)
	{
	  current_size += (int)nread;
	  if (new_file_fd != -1)
	    write(new_file_fd, buf, strlen(buf));
	  ftp_send(cli->socket, "OK\n", 3);
	  bzero(buf, sizeof(buf));
	}
      usleep(500);
      ftp_send(cli->socket, "[Server] upload success\n", 24);
    }
  else
      ftp_send(cli->socket, "[Server] upload failed\n", 24);
}

void exec_put(t_cli *cli, char *opt)
{
  char *file_name;

  file_name = extract_file_name(opt);
  ftp_send(cli->socket, "[Server] waiting transmission\n", 34);

  if (file_name)
    {
      file_name = strtok(file_name, "\n");
      file_name[strlen(file_name)] = '\0';
    }
  file_name = transform_file_name(cli, file_name);
  execputs(cli, file_name, 0);
}
