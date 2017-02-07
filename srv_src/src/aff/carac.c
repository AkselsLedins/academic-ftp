/*
** carac.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src/aff
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 18:56:19 2014 ledins
** Last update Sun Apr 13 18:56:30 2014 ledins
*/

#include <stdio.h>
#include <string.h>
#include "ftp.h"

void print_carac(char *statement, int value, int default_value)
{
printf("~ %s: %s%d%s", statement, COLOR_Y , value, COLOR_DEFAULT);
printf((value == default_value ? " (default_value)\n" : "\n"));
}

void print_carac_db(char *value)
{
printf("~ database     : %s%s%s\n", COLOR_Y, value, COLOR_DEFAULT);
printf((strcmp(value, DEFAULT_DB) == 0 ? " (default_value)\n" : "\n"));
}
