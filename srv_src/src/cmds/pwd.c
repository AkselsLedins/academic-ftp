/*
** pwd.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cmds
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 19:59:59 2014 ledins
** Last update Sun Apr 13 20:00:23 2014 ledins
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

void exec_pwd(t_cli *cli, char *opt)
{
char path[PATH_MAX];

(void)opt;
bzero(path, sizeof(path));
sprintf(path, "%s\n", cli->current_dir);
ftp_send(cli->socket, path, strlen(path));
}
