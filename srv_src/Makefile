NAME = serveur

CC = gcc

DIR_SRC	= ./src/

INC_DIR = ./inc/

SRC = $(DIR_SRC)main.c \
	$(DIR_SRC)aff/text.c \
	$(DIR_SRC)aff/carac.c \
	$(DIR_SRC)cli/secure.c \
	$(DIR_SRC)cli/cli.c \
	$(DIR_SRC)db/user.c \
	$(DIR_SRC)db/com.c \
	$(DIR_SRC)db/login.c \
	$(DIR_SRC)network.c \
	$(DIR_SRC)init.c \
	$(DIR_SRC)parsing.c \
	$(DIR_SRC)server.c \
	$(DIR_SRC)exec.c \
	$(DIR_SRC)tools.c \
	$(DIR_SRC)cmds/ls.c \
	$(DIR_SRC)cmds/get.c \
	$(DIR_SRC)cmds/cd.c \
	$(DIR_SRC)cmds/put.c \
	$(DIR_SRC)cmds/pwd.c

CFLAGS = -Wall -Wextra 
## -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INC_DIR)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lsqlite3

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
