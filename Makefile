CC = cc
FLAGS = -Wextra -Werror -Wall #-fsanitize=address -g
SRC = minishell.c builtins.c execute.c free.c
LIBFT = make -C ./libft
NAME = minishell
OBJ = $(SRC:.c=.o)

all : ${NAME}

${NAME} : ${SRC}
	make bonus -C ./libft
	${CC} ${FLAGS} ${SRC} -lreadline ./libft/libft.a -o ${NAME}

clean : 
	rm -rf $(OBJ)
	make clean -C ./libft

fclean : clean 
	make fclean -C ./libft
	rm -rf ${NAME}

re : fclean all