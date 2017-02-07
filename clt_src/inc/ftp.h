/*
** ftp.h for client_ftp in /home/ledins_a/Dropbox/my_ftp/clt_src/inc
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 16:01:07 2014 ledins
** Last update Sun Apr 13 16:01:44 2014 ledins
*/

/* standards */
#include <unistd.h>
#include <stdlib.h>

/* socket */
#include <sys/types.h>
#include <sys/socket.h>

/* protocole */
#include <netdb.h>

/* inet_ntoa */
#include <netinet/in.h>
#include <arpa/inet.h>

/* sql */
#include <sqlite3.h>

/* FILE */
#include <stdio.h>

#ifndef FTP_H
# define FTP_H

/* colors */
#define COLOR_DEFAULT "\033[0;0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_Y "\033[0;33m"

/* default values */
#define FTP_SUCCESS 1
#define FTP_FAILURE -1
#define DEFAULT_MNUM "1337"

/* cmds values */
#define CMD_LS  0
#define CMD_CD  1
#define CMD_GET 2
#define CMD_PUT 3
#define CMD_PWD 4
#define CMD_QUIT 5
#define CMD_LOGIN 6
#define CMD_CREATE 7

/* enums */
typedef enum e_boolean { FALSE = 0, TRUE = 1 } e_boolean;

/* networking */
typedef struct s_network
{
	struct sockaddr_in sin;
	struct protoent *protocole;
	int port;
	int socket;
	int quiet;
	char *magicNumber;
	char *bin_path;
	char *ip;
} t_network;

/* prototypes */
/* network.c */
void ftp_close(t_network *network);
void ftp_socket(t_network *network);
void ftp_connect(t_network *network);

/* init.c */
t_network * init_network(t_network *network, int argc, char **argv);

/* tools.c */
int usage(char *prog);
ssize_t ftp_send(int sockfd, const void *buf, size_t len);
ssize_t ftp_recv(int sockfd, void *buf, size_t len);
void tej_retourchariot(char *buf);
char *delete_first_spaces(char *raw);

/* secure.c */
void send_magic_number(t_network *n);

/* ftp.c */
void ftp_run(t_network *network);

/* put.c */
int exec_put(t_network *network, char *opt);

/* get.c */
int exec_get(t_network *network, char *cmd);

/* cmd.c */
int parsing_cmd(char *raw);

/* transmission.c */
void transmit_file(t_network *network, FILE *fd);
int filesize(FILE *fp);
int ftp_check_file(char *path);

#endif /* ! ftp.h */
