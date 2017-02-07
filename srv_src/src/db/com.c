/*
** com.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/db
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 18:48:02 2014 ledins
** Last update Sun Apr 13 18:48:05 2014 ledins
*/

#include "ftp.h"

void db_user_already_exist(t_cli *cli)
{
ftp_send(cli->socket, "[Server] this user already exists !\n", 36);
}
