/*
** main.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:38:47 2014 ledins
** Last update Sun Apr 13 18:41:05 2014 ledins
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ftp.h"

void create_ftp_folder()
{
  struct stat s;
  int err = stat("./cli_ftp", &s);

  if (err != -1)
    {
      if (!S_ISDIR(s.st_mode))
	{
	  fprintf(stderr, "Err : can't create ftp folder for users\n");
	  exit(EXIT_FAILURE);
	}
    }
  else
    mkdir("./cli_ftp", S_IRWXU | S_IRWXG | S_IRWXO);
}

int main(int argc, char **argv)
{
  t_network *network;

  welcome_message();
  create_ftp_folder();
  if (ftp_init(&network, argc, argv) == FTP_FAILURE)
    return (EXIT_FAILURE);
  ftp_socket(network);
  ftp_reuseaddr(network);
  ftp_bind(network);
  ftp_listen(network);
  server_start(network);
  ftp_close(network);
  return (EXIT_SUCCESS);
}
