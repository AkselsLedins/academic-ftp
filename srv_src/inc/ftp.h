/*
** ftp.h for ftp_server in /home/ledins_a/Dropbox/my_ftp/srv_src/inc
**
** Made by ledins
** Login   <ledins_a@epitech.net>
**
** Started on  Sun Apr 13 20:02:57 2014 ledins
** Last update Sun Apr 13 20:03:52 2014 ledins
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

/* default values */
#define DEFAULT_PORT 4550
#define DEFAULT_MNUM 1337
#define DEFAULT_QUEUE 3
#define DEFAULT_DB "cli.db"

#define QUEUE_LEN 3
#define FTP_SUCCESS 1
#define FTP_FAILURE -1

/* buffers */
#define LEN_BUFFER 225
#define LEN_USERNAME 25
#define LEN_PASSWORD 40
#define LEN_DBNAME 15

/* colors */
#define COLOR_DEFAULT "\033[0;0m"
#define COLOR_RED "\033[0;34m"
#define COLOR_Y "\033[0;33m"

/* options */
#define OPT_PORT 'p'
#define OPT_QUIET 'q'
#define OPT_MNUM 'x'
#define OPT_QUEUE 'w'
#define OPT_DB 'd'

/* commands */
#define CMD_LS  0
#define CMD_CD  1
#define CMD_GET 2
#define CMD_PUT 3
#define CMD_PWD 4
#define CMD_QUIT 5
#define CMD_LOGIN 6
#define CMD_CREATE 7

#define LEN_CMD (CMD_QUIT + 1)

/* db */
#define DB_UE "SELECT username FROM cli WHERE username='%s'"
#define DB_ADD "INSERT INTO cli(username, password) VALUES('%s', '%s');"

/* statement */
#define V_QT "\t%s-%c%s         : quiet mode\n"
#define V_P "\t%s-%c%s [port]  : spec port\n"
#define V_DB "\t%s-%c%s [name]  : spec db name\n"
#define V_W "\t%s-%c%s [queue]  : spec queue\n"
#define V_M "\t%s-%c%s [magic] : spec magic number\n\n\n"

/* enums */
typedef enum e_boolean { FALSE = 0, TRUE = 1 } e_boolean;

/* CD structure */
typedef struct s_cd
{
	struct s_cd *next;
	char *path;
} t_cd;

/* networking */
typedef struct s_network
{
	struct sockaddr_in sin;
	struct sockaddr_in sin_client;
	struct protoent *protocole;
	int port;
	int socket;
	int quiet;
	int magicNumber;
	int queue;
	sqlite3 *db;
	char db_name[LEN_DBNAME];
	char *bin_path;
} t_network;

/* cli */
typedef struct s_cli
{
	int socket;
	char username[LEN_USERNAME];
	char password[LEN_PASSWORD];
	e_boolean authenticated;
	char *root_dir;
	t_cd *lroot_dir;
	t_cd *lcurrent_dir;
	char *current_dir;
	void (*tab_f[LEN_CMD])(struct s_cli *, char *);
} t_cli;

/* functions prototypes */
/* text.c */
void welcome_message();
void ask_username(t_cli *cli);
void ask_password(t_cli *cli);
void invalid_command(t_cli *cli);
void login_first_please(t_cli *cli);

/* init.c */
int ftp_init(t_network **raw, int argc, char **argv);

/* parsing.c */
int parsing_option(int argc, char **argv, int flag);
int parsing_option_exist(int argc, char **argv, int flag);
char * parsing_option_db(int argc, char **argv, char *buf, sqlite3 **db);

/* tools.c */
int is_option(char *opt, int flag);
int is_integer(char *str);
ssize_t ftp_recv(int sockfd, void *buf, size_t len);
ssize_t ftp_send(int sockfd, const void *buf, size_t len);
int filesize(FILE *fp);

/* carac.c */
void print_carac(char *statement, int value, int default_value);
void print_carac_db(char *value);

/* network.c */
void ftp_socket(t_network *network);
void ftp_bind(t_network *network);
void ftp_reuseaddr(t_network *network);
void ftp_close(t_network *network);
void ftp_listen(t_network *network);

/* server.c */
void server_start(t_network *network);

/* cli.c */
void ftp_cli(t_network *network, int cli_sock);

/* exec(*).c */
char *extract_path(char *opt);
char *delete_n_first_char(char *str, size_t n);
char *cd_fix_repo(char *repo);
char *extract_file_name(char *opt);
void transmit_file(t_cli *cli, FILE *fd);
void exec_ls(t_cli *cli, char *opt);
void exec_cd(t_cli *cli, char *opt);
void exec_get(t_cli *cli, char *opt);
void exec_pwd(t_cli *cli, char *opt);
void exec_put(t_cli *cli, char *opt);
void exec_quit(t_cli *cli, char *opt);

/* secure.c */
void authenticate(t_network *network, t_cli *cli, char *);
void try_magic_number(t_network *network, t_cli *cli);
void authenticate_user_acreat(t_cli *cli);

/* db.c */
void db_login(t_network *network, t_cli *cli);
void db_adduser(t_network *network, t_cli *cli);
void db_init(t_network *network);

/* db com */
void db_user_already_exist(t_cli *cli);

/* cd_list.c */
t_cd * concat_list(t_cd *root, t_cd *new);
t_cd * path_to_list(char *path);
void add_node_end(t_cd **raw, char *path);
int len_cd(t_cd *act);
int delete_node_end_clen(t_cd **act, int len_root);

/* cd_list_tools.c */
void print_list_path(t_cd *path);
char *list_to_char(t_cd *path);
void list_to_list(t_cd **dest, t_cd *src);
void free_list(t_cd **list);

/* db.c */
int callback(void *NotUsed, int argc, char **argv, char **azColName);
void db_login_ok(t_network *network, t_cli *cli, int flag);

#endif // FTP_H
