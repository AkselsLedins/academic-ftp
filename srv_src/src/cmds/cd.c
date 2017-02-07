/*
** cd.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cmds
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 19:47:48 2014 ledins
** Last update Sun Apr 13 19:51:39 2014 ledins
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

void exec_cd_from_root(t_cli *cli, char *option)
{
  char buf[PATH_MAX];
  char *new_path;

  bzero(buf, PATH_MAX);
  strcpy(buf, cli->root_dir);
  strcat(buf, option);
  new_path = realpath(buf, NULL);
  if (new_path)
    {
      if (strlen(new_path) >= strlen(cli->root_dir)
	  && strncmp(new_path, cli->root_dir, strlen(cli->root_dir)) == 0)
	{
	  if (chdir(new_path) != -1)
	    {
	      cli->current_dir = delete_n_first_char(new_path,
						     strlen(cli->root_dir));
	      cli->current_dir = cd_fix_repo(cli->current_dir);
	      bzero(buf, PATH_MAX);
	      sprintf(buf, "%s\n", cli->current_dir);
	      ftp_send(cli->socket, buf, strlen(buf));
	    }
	}
      else
	ftp_send(cli->socket, "[Server] no such directory\n", 27);
    }
}

static void execrepoif(t_cli *cli, char *new_path, char *buf, char *option)
{
  char error[250];

  if (chdir(new_path) != -1)
    {
      cli->current_dir = delete_n_first_char(new_path, strlen(cli->root_dir));
      cli->current_dir = cd_fix_repo(cli->current_dir);
      bzero(buf, PATH_MAX);
      sprintf(buf, "%s\n", cli->current_dir);
      ftp_send(cli->socket, buf, strlen(buf));
    }
  else
    {
      bzero(error, 250);
      sprintf(error, "[Server] %s : %s\n", option, strerror(errno));
      ftp_send(cli->socket, error, strlen(error));
    }
}

void exec_cd_from_cur_repo(t_cli *cli, char *option)
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
	execrepoif(cli, new_path, buf, option);
      else
	ftp_send(cli->socket, "[Server] no such directory\n", 27);
    }
  else
    ftp_send(cli->socket, "[Server] no such directory\n", 27);
}

void exec_cd_back_home(t_cli *cli)
{
  if (chdir(cli->root_dir) == -1)
    {
      printf("Home fucked up, exiting !\n");
      exit(EXIT_FAILURE);
    }
  ftp_send(cli->socket, "/\n", 2);
  cli->current_dir = strdup("/");
}

void exec_cd(t_cli *cli, char *opt)
{
  char *option;

  option = extract_path(opt);
  if (option)
    {
      option = strtok(option, "\n");
      option[strlen(option)] = '\0';
      if (option[0] == '/')
	exec_cd_from_root(cli, option);
      else
	exec_cd_from_cur_repo(cli, option);
      free(option);
    }
  else
    exec_cd_back_home(cli);
}
