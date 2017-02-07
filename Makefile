NAME_SRV = serveur
NAME_CLT = client

PATH_SRV = ./srv_src/
PATH_CLT = ./clt_src/

RM = rm -f

all: client serveur

client:
	make -C $(PATH_CLT) re && cp $(PATH_CLT)$(NAME_CLT) ./

serveur:
	make -C $(PATH_SRV) re && cp $(PATH_SRV)$(NAME_SRV) ./

clean:
	make -C $(PATH_CLT) clean
	make -C $(PATH_SRV) clean


fclean: 
	make -C $(PATH_CLT) fclean
	make -C $(PATH_SRV) fclean
	$(RM) $(NAME_SRV)
	$(RM) $(NAME_CLT)

re: fclean all
