/*
** ls.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cmds
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 19:53:45 2014 ledins
** Last update Sun Apr 13 19:53:53 2014 ledins
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

void exec_ls(t_cli *cli, char *opt)
{
  char buf[PATH_MAX];
  DIR *dir;
  struct dirent *e;

  (void)opt;
  bzero(buf, PATH_MAX);
  strcpy(buf, cli->root_dir);
  strcat(buf, cli->current_dir);
  if ((dir = opendir (buf)) != NULL)
    {
      bzero(buf, PATH_MAX);
      while ((e = readdir (dir)) != NULL)
	{
	  if (!(cli->current_dir[0] == '/' && strcmp(e->d_name, "..") == 0))
	    {
	      strcat(buf, e->d_name);
	      strcat(buf, " ");
	    }
	}
      strcat(buf, "\n");
      ftp_send(cli->socket, buf, strlen(buf));
      closedir (dir);
    }
}
