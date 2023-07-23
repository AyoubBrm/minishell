CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g #-Wextra -Wall
SRC =	minishell.c execute.c free.c account_the_quote.c clean_expand.c free_link_list.c syntax_error.c ambiguous_no_dirc.c\
		get_token_par.c num_of_alloc_str.c str_without_quote_and_dollar.c token_v2.c join_with_2Darr.c join_with_2Darr_with_1Darr.c str_inside_double_qoute.c\
		str_inside_single_qoute.c heredoc_expand.c expand.c find_var_in_env.c space_inside_env_and_no_expand.c final_list.c addition_input_rid.c addition_part.c\
		check_ambig.c addition_cmd.c\
		cmd_checks.c\
		redirections.c\

SRC_BUILTINS	=	$(addprefix ./builtins/, echo.c exit.c export.c env.c cd.c pwd.c unset.c)

LIBFT = make -C ./libft

FT_PRINTF	=	make -C ./ft_printf

NAME = minishell
OBJ = $(SRC:.c=.o)

all : ${NAME}

${NAME} : ${SRC}
	make bonus -C ./libft
	$(FT_PRINTF)
	${CC} $(FLAGS) ${SRC} $(SRC_BUILTINS) -lreadline ./libft/libft.a ./ft_printf/libftprintf.a -o ${NAME}

clean : 
	rm -rf $(OBJ)
	make clean -C ./libft
	make clean -C ./ft_printf

fclean : clean 
	make fclean -C ./libft
	make fclean -C ./ft_printf
	rm -rf ${NAME}

re : fclean all