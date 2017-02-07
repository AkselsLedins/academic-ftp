NAME = client

CC = gcc

DIR_SRC	= ./src/

INC_DIR = ./inc/

SRC = $(DIR_SRC)main.c \
	$(DIR_SRC)init.c \
	$(DIR_SRC)network.c \
	$(DIR_SRC)secure.c \
	$(DIR_SRC)tools.c \
	$(DIR_SRC)ftp.c \
	$(DIR_SRC)put.c \
	$(DIR_SRC)get.c \
	$(DIR_SRC)cmd.c \
	$(DIR_SRC)transmission.c

CFLAGS = -Wall -Wextra 
## -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INC_DIR)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
