CC = cc
FLAGS = -Wextra -Werror -Wall #
SRC = minishell.c
LIBFT = make -C ./libft
NAME = minishell
OBJ = $(SRC:.c=.o)

all : ${NAME}

${NAME} : ${SRC}
	make -C ./libft
	${CC} ${FLAGS} ${SRC} -lreadline ./libft/libft.a -o ${NAME}

clean : 
	rm -rf $(OBJ)
	make clean -C ./libft

fclean : clean 
	make fclean -C ./libft
	rm -rf ${NAME}

re : fclean all