/*
** parsing.c for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/src
** 
** Made by ledins
** Login   <ledins_a@epitech.net>
** 
** Started on  Sun Apr 13 18:36:53 2014 ledins
** Last update Sun Apr 13 18:46:18 2014 ledins
*/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "ftp.h"

int default_value(int flag)
{
  if (flag == OPT_PORT)
    return (DEFAULT_PORT);
  if (flag == OPT_MNUM)
    return (DEFAULT_MNUM);
  if (flag == OPT_QUEUE)
    return (DEFAULT_QUEUE);
  return (FTP_FAILURE);
}

int parsing_option(int argc, char **argv, int flag)
{
  int ii;

  ii = 1;
  while (ii < argc)
    {
      if (strlen(argv[ii]) == 2)
	{
	  if (is_option(argv[ii], flag) == FTP_SUCCESS)
	    {
	      ii++;
	      if (ii < argc)
		{
		  if (is_integer(argv[ii]) == FTP_SUCCESS)
		    return (atoi(argv[ii]));
		}
	      return (default_value(flag));
	    }
	}
      ii++;
    }
  return (default_value(flag));
}

int parsing_option_exist(int argc, char **argv, int flag)
{
  int ii;

  ii = 1;
  while (ii < argc)
    {
      if (strlen(argv[ii]) == 2)
	{
	  if (is_option(argv[ii], flag) == FTP_SUCCESS)
	    return (FTP_SUCCESS);
	}
      ii++;
    }
  return (FTP_FAILURE);
}

char *parsing_getname_db(int argc, char **argv)
{
  int ii;

  ii = 1;
  while (ii < argc)
    {
      if (strlen(argv[ii]) == 2)
	{
	  if (is_option(argv[ii], OPT_DB) == FTP_SUCCESS)
	    {
	      ii++;
	      if (ii < argc)
		{
		  return (argv[ii]);
		}
	      return (DEFAULT_DB);
	    }
	}
      ii++;
    }
  return (DEFAULT_DB);
}

char *parsing_option_db(int argc, char **argv, char *buf, sqlite3 **db)
{
  int rc;

  buf = parsing_getname_db(argc, argv);
  rc = sqlite3_open(buf, db);
  if (rc)
    exit(EXIT_FAILURE);
  return (buf);
}
