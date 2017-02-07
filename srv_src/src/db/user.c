/*
** user.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/db
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:52:16 2014 ledins
** Last update Sun Apr 13 18:55:36 2014 ledins
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ftp.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  static int k;
  int i;

  if (argc == -42)
    {
      i = k;
      k = 0;
      return (i);
    }
  if (argc == 0)
    {
      k = 0;
      return (0);
    }
  k = 1;
  (void)argv;
  (void)azColName;
  (void)argc;
  (void)NotUsed;
  return (k);
}

void db_init(t_network *network)
{
  char *req_sql;
  int rc;
  char *zErrMsg = 0;

  req_sql = "SELECT * FROM cli;";
  rc = sqlite3_exec(network->db, req_sql, NULL, 0, &zErrMsg);
  if (rc != SQLITE_OK)
    {
      if (network->quiet == FTP_FAILURE)
	printf("Preparing the database..\n");
      req_sql = "CREATE TABLE cli(id INTEGER PRIMARY KEY \
    		AUTOINCREMENT, username CHAR(25) NOT NULL, password \
    		CHAR(40) NOT NULL);";
      rc = sqlite3_exec(network->db, req_sql, callback, 0, &zErrMsg);
      if (rc != SQLITE_OK)
    	{
	  sqlite3_free(zErrMsg);
	  exit(EXIT_FAILURE);
    	}
      if (network->quiet == FTP_FAILURE)
	printf(".. with success !\n");
    }
}

void db_sql_adduser(t_network *network, t_cli *cli)
{
  char buffer[100];
  int rc;
  char *zErrMsg;

  zErrMsg = 0;
  bzero(buffer, 100);
  sprintf(buffer, DB_UE, cli->username);
  callback(NULL, -42, NULL, NULL);
  rc = sqlite3_exec(network->db, buffer, callback, NULL, &zErrMsg);
  if (callback(NULL, -42, NULL, NULL) == 0)
    {
      sprintf(buffer, DB_ADD, cli->username, cli->password);
      rc = sqlite3_exec(network->db, buffer, callback, NULL, &zErrMsg);
      if (rc != SQLITE_OK)
	sqlite3_free(zErrMsg);
      else
    	{
	  db_login_ok(network, cli, 0);
	  authenticate_user_acreat(cli);
    	}
    }
  else
    db_user_already_exist(cli);

}

void db_adduser(t_network *network, t_cli *cli)
{
  int read;
  ask_username(cli);
  read = ftp_recv(cli->socket, cli->username, LEN_USERNAME);
  cli->username[read] = '\0';
  ask_password(cli);
  read = ftp_recv(cli->socket, cli->password, LEN_PASSWORD);
  cli->password[read] = '\0';
  db_sql_adduser(network, cli);
}
