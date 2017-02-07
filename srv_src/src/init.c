/*
** init.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:35:27 2014 ledins
** Last update Sun Apr 13 18:44:39 2014 ledins
*/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <linux/limits.h>
#include "ftp.h"

int ftp_init(t_network **raw, int argc, char **argv)
{
  t_network *n;

  if ((n = malloc(sizeof(t_network))) == NULL)
    return (FTP_FAILURE);
  n->port = parsing_option(argc, argv, OPT_PORT);
  n->protocole = getprotobyname("TCP");
  n->quiet = parsing_option_exist(argc, argv, OPT_QUIET);
  n->magicNumber = parsing_option(argc, argv, OPT_MNUM);
  n->queue = parsing_option(argc, argv, OPT_QUEUE);
  n->bin_path = malloc(PATH_MAX);
  n->bin_path = getcwd(n->bin_path, PATH_MAX);
  if (n->quiet == FTP_FAILURE)
    {
      print_carac("port         ", n->port, DEFAULT_PORT);
      print_carac("magicNumber  ", n->magicNumber, DEFAULT_MNUM);
      print_carac("listen queue ", n->queue, DEFAULT_QUEUE);
      print_carac_db(parsing_option_db(argc, argv, n->db_name, &n->db));
      printf("~ prot         : %sTCP%s\n\n", COLOR_Y, COLOR_DEFAULT);
    }
  db_init(n);
  *raw = n;
  return (FTP_SUCCESS);
}
