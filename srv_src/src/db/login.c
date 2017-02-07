/*
** login.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/db
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 18:48:43 2014 ledins
** Last update Sun Apr 13 18:51:35 2014 ledins
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ftp.h"

static void db_login_ok_create_repo(char *path)
{
  struct stat s;
  int err;

  err = stat(path, &s);
  if (err != -1)
    {
      if (!S_ISDIR(s.st_mode))
	{
	  if (remove(path) == -1)
	    {
	      perror("");
	      exit(EXIT_FAILURE);
	    }
	  db_login_ok_create_repo(path);
	}
    }
  else
    mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
}

void db_login_ok(t_network *network, t_cli *cli, int flag)
{
  size_t size;

  if (flag != 0)
    ftp_send(cli->socket, "[Server] you are connected !\n", 29);
  cli->authenticated = TRUE;
  size = strlen(network->bin_path)
    + strlen("/cli_ftp/")
    + strlen(cli->username) + 1;
  cli->root_dir = malloc(size);
  bzero(cli->root_dir, size);
  strcpy(cli->root_dir, network->bin_path);
  strcat(cli->root_dir, "/cli_ftp/");
  strcat(cli->root_dir, cli->username);
  cli->current_dir = strdup("/");
  db_login_ok_create_repo(cli->root_dir);
}

static void db_login_init(t_network *network, t_cli *cli)
{
  char b[100];
  char *zErrMsg;

  zErrMsg = 0;
  bzero(b, 100);
  sprintf(b, "SELECT username FROM cli WHERE username='%s' AND password='%s';",
	  cli->username, cli->password);
  callback(NULL, -42, NULL, NULL);
  sqlite3_exec(network->db, b, callback, NULL, &zErrMsg);
  if (callback(NULL, -42, NULL, NULL) == 0)
    ftp_send(cli->socket, "[Server] bad login/password\n", 28);
  else
    db_login_ok(network, cli, 1);
}

void db_login(t_network *network, t_cli *cli)
{
  ssize_t read;

  ftp_send(cli->socket, "[Server] please enter your login ?\n", 35);
  read = ftp_recv(cli->socket, cli->username, LEN_USERNAME);
  cli->username[read] = '\0';
  ftp_send(cli->socket, "[Server] please enter your password ?\n", 40);
  read = ftp_recv(cli->socket, cli->password, LEN_PASSWORD);
  cli->password[read] = '\0';
  db_login_init(network, cli);
}
