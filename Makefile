CC = cc
FLAGS = -Wextra -Werror -Wall #-fsanitize=address -g
SRC = minishell.c builtins.c execute.c free.c account_the_quote.c clean_expand.c free_link_list.c syntax_error.c ambiguous_no_dirc.c\
	  get_token_par.c num_of_alloc_str.c str_without_quote_and_dollar.c token_v2.c join_with_2Darr.c join_with_2Darr_with_1Darr.c str_inside_double_qoute.c str_inside_single_qoute.c
LIBFT = make -C ./libft
NAME = minishell
OBJ = $(SRC:.c=.o)

all : ${NAME}

${NAME} : ${SRC}
	make bonus -C ./libft
	${CC} ${FLAGS} ${SRC} -lreadline -L /Users/abouram/goinfre/homebrew/opt/readline/lib -I /Users/abouram/goinfre/homebrew/opt/readline/include ./libft/libft.a  -o ${NAME}

clean : 
	rm -rf $(OBJ)
	make clean -C ./libft

fclean : clean 
	make fclean -C ./libft
	rm -rf ${NAME}

re : fclean all