/*
** cmd.c for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/src
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 15:50:56 2014 ledins
** Last update Sun Apr 13 15:56:24 2014 ledins
*/

#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ftp.h"

static void getcmd(char *cmd, char *raw)
{
  int i;
  int k;

  i = 0;
  k = 0;
  bzero(cmd, 30);
  while (raw && (raw[i] == ' ' || raw[i] == '\t'))
    i++;
  while (raw && raw[i] != ' ' && raw[i] != '\t' && k < 29)
    {
      cmd[k] = raw[i];
      k++;
      i++;
    }
  cmd[k] = '\0';
}

static char return_id_cmd(char *cmd)
{
  if (strcmp(cmd, "ls") == 0)
    return (CMD_LS + '0');
  else if (strcmp(cmd, "cd") == 0)
    return (CMD_CD + '0');
  else if (strcmp(cmd, "get") == 0)
    return (CMD_GET + '0');
  else if (strcmp(cmd, "put") == 0)
    return (CMD_PUT + '0');
  else if (strcmp(cmd, "pwd") == 0)
    return (CMD_PWD + '0');
  else if (strcmp(cmd, "quit") == 0)
    return (CMD_QUIT + '0');
  else if (strcmp(cmd, "login") == 0)
    return (CMD_LOGIN + '0');
  else if (strcmp(cmd, "register") == 0)
    return (CMD_CREATE + '0');
  else
    return ('n');
}

static void replace_tab(char *raw)
{
  int i;

  i = 0;
  while (raw && raw[i])
    {
      if (raw[i] == ' ')
	raw[i] = '\t';
      i++;
    }
}

static void transfer_option(char *raw, char *cmd)
{
  int i;
  int k;

  i = 0;
  k = 2;
  while (raw && (raw[i] == ' ' || raw[i] == '\t'))
    i++;
  while (raw && raw[i] != '\0' &&
	 raw[i] != ' ' && raw[i] != '\t' && k < 40)
    i++;
  while (raw && (raw[i] == ' ' || raw[i] == '\t'))
    i++;
  while (raw && raw[i] != ' ' && raw[i] != '\t'
	 && raw[i] != '\0'&& k < 40)
    {
      cmd[k] = raw[i];
      k++;
      i++;
    }
  cmd[k] = '\0';
}

int parsing_cmd(char *raw)
{
  char buf[1024];
  char cmd[40];

  raw = delete_first_spaces(raw);
  tej_retourchariot(raw);
  replace_tab(raw);
  bzero(buf, 1024);
  getcmd(cmd, raw);
  buf[0] = return_id_cmd(cmd);
  buf[1] = ' ';
  transfer_option(raw, buf);
  if (buf[0] != 'n')
    {
      bzero(raw, 1024);
      strcpy(raw, buf);
    }
  return (buf[0] - '0');
}
