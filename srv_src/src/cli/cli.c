/*
** cli.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/cli
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 19:00:41 2014 ledins
** Last update Sun Apr 13 19:00:44 2014 ledins
*/

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include "ftp.h"

void get_cmd(char buf[], int cli_sock)
{
  bzero(buf, LEN_BUFFER);
  ftp_recv(cli_sock, buf, LEN_BUFFER - 1);
}

void ftp_init_cli(t_cli **raw, int cli_sock)
{
  t_cli *cli;

  cli = malloc(sizeof(t_cli));
  if (!cli)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  cli->tab_f[0] = &exec_ls;
  cli->tab_f[1] = &exec_cd;
  cli->tab_f[2] = &exec_get;
  cli->tab_f[3] = &exec_put;
  cli->tab_f[4] = &exec_pwd;
  cli->authenticated = FALSE;
  cli->socket = cli_sock;
  *raw = cli;
}

void ftp_execute_command(t_network *network, t_cli *cli, char buf[])
{
  if ((int)buf[0] - 48 == CMD_LOGIN)
    db_login(network, cli);
  else if ((int)buf[0] - 48 == CMD_CREATE)
    db_adduser(network, cli);
  else if ((int)buf[0] - 48 == CMD_QUIT)
    {
      printf("exiting client !\n");
      exit(EXIT_SUCCESS);
    }
  else if (cli->authenticated == FALSE && (int)buf[0] - 48 < CMD_QUIT)
    login_first_please(cli);
  else if ((int)buf[0] - 48 > CMD_QUIT )
    invalid_command(cli);
  else
    (cli->tab_f[buf[0] - 48])(cli, buf);
}

void ftp_cli(t_network *network, int cli_sock)
{
  t_cli *cli;
  char buf[LEN_BUFFER];

  ftp_init_cli(&cli, cli_sock);
  try_magic_number(network, cli);
  while (TRUE)
    {
      get_cmd(buf, cli_sock);
      ftp_execute_command(network, cli, buf);
    }
}
