/*
** get.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cmds
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 19:52:55 2014 ledins
** Last update Sun Apr 13 19:53:20 2014 ledins
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

static int ftp_check_file(t_cli *cli, char *path)
{
  int status;
  struct stat st_buf;

  status = stat(path, &st_buf);
  if (status != 0)
    {
      ftp_send(cli->socket, "[Server] file does not exists\n", 30);
      return (-1);
    }
  if (S_ISDIR (st_buf.st_mode))
    {
      ftp_send(cli->socket, "[Server] file requested is a directory\n", 39);
      return (-1);
    }
  return (0);
}

static void send_file(t_cli *cli, char *path)
{
  char error[250];
  FILE *fd_file;

  if (ftp_check_file(cli, path) == -1)
    return;
  fd_file = fopen(path, "rb");
  if (fd_file)
    {
      transmit_file(cli, fd_file);
      fclose(fd_file);
      ftp_send(cli->socket, "[Server] transmission terminated\n" , 33);
    }
  else
    {
      bzero(error, 250);
      sprintf(error, "[Server] get : %s\n", strerror(errno));
      ftp_send(cli->socket, error, strlen(error));
    }
}

static void exec_get_from_root(t_cli *cli, char *option)
{
  char buf[PATH_MAX];
  char *new_path;

  bzero(buf, PATH_MAX);
  strcpy(buf, cli->root_dir);
  if (cli->root_dir[strlen(cli->root_dir) - 1] != '/'
      && cli->current_dir[strlen(cli->current_dir) - 1] != '/')
    strcat(buf, "/");
  strcat(buf, option);
  new_path = realpath(buf, NULL);
  if (new_path)
    {
      if (strlen(new_path) >= strlen(cli->root_dir)
	  && strncmp(new_path, cli->root_dir, strlen(cli->root_dir)) == 0)
	send_file(cli, new_path);
      else
	{
	  ftp_send(cli->socket, "[Server] get : no such file\n", 34);
	}
    }
  else
    {
      ftp_send(cli->socket, "[Server] get : no such file\n", 34);
    }
}

static void exec_get_from_cur_repo(t_cli *cli, char *option)
{
  char buf[PATH_MAX];
  char *new_path;

  bzero(buf, PATH_MAX);
  strcpy(buf, cli->root_dir);
  strcat(buf, cli->current_dir);
  if (cli->root_dir[strlen(cli->root_dir) - 1] != '/'
      && cli->current_dir[strlen(cli->current_dir) - 1] != '/')
    strcat(buf, "/");
  strcat(buf, option);
  new_path = realpath(buf, NULL);
  if (new_path)
    {
      if (strlen(new_path) >= strlen(cli->root_dir)
	  && strncmp(new_path, cli->root_dir, strlen(cli->root_dir)) == 0)
	send_file(cli, new_path);
      else
	{
	  ftp_send(cli->socket, "[Server] get : no such file\n", 34);
	}
    }
  else
    {
      ftp_send(cli->socket, "[Server] get : no such file\n", 34);
    }
}

void exec_get(t_cli *cli, char *opt)
{
  char *option;

  option = extract_file_name(opt);
  if (option)
    {
      option = strtok(option, "\n");
      option[strlen(option)] = '\0';
      if (option[0] == '/')
	exec_get_from_root(cli, option);
      else
	exec_get_from_cur_repo(cli, option);
    }
}
