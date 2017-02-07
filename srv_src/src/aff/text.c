/*
** text.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/aff
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 18:57:00 2014 ledins
** Last update Sun Apr 13 18:59:06 2014 ledins
*/

#include <stdio.h>
#include "ftp.h"

void welcome_message()
{
  printf("\n\n\tWelcome on ledins_a my_ftp\n");
  printf("\t- Author  : ledins_a\n\n");
  printf(V_P, COLOR_RED, OPT_PORT, COLOR_DEFAULT);
  printf(V_DB, COLOR_RED, OPT_DB, COLOR_DEFAULT);
  printf(V_W, COLOR_RED, OPT_QUEUE, COLOR_DEFAULT);
  printf(V_M, COLOR_RED, OPT_MNUM, COLOR_DEFAULT);
}

void ask_password(t_cli *cli)
{
  ftp_send(cli->socket, "[Server] enter your new password ?\n", 35);
}

void ask_username(t_cli *cli)
{
  ftp_send(cli->socket, "[Server] enter your new username ?\n", 35);
}

void invalid_command(t_cli *cli)
{
  printf("jenvoie invalid command\n");
  ftp_send(cli->socket, "[Server] invalid command !\n", 27);
}

void login_first_please(t_cli *cli)
{
  ftp_send(cli->socket, "[Server] login or register first\n", 33);
}
