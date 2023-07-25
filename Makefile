CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L/Users/abouram/goinfre/homebrew/opt/readline/lib -I/Users/abouram/goinfre/homebrew/opt/readline/include -lreadline

SRC = minishell.c
SRC_BUILTINS = $(addprefix ./builtins/, echo.c exit.c export.c export_utils.c myexport_utils2.c env.c cd.c pwd.c unset.c)
SRC_EXECUTION = $(addprefix ./execution/, init.c execute.c cmd_checks.c redirections_utils.c signals.c heredoc_utils.c exec_utils.c init_n_destroy.c pipes_n_redir.c redirections.c)
SRC_PARSER = $(addprefix ./parser/, free.c account_the_quote.c clean_expand.c free_link_list.c syntax_error.c ambiguous_no_dirc.c get_token_par.c num_of_alloc_str.c str_without_quote_and_dollar.c token_v2.c join_with_2Darr.c join_with_2Darr_with_1Darr.c str_inside_double_qoute.c str_inside_single_qoute.c heredoc_expand.c expand.c find_var_in_env.c space_inside_env_and_no_expand.c final_list.c addition_input_rid.c addition_part.c check_ambig.c token_without_quotev2.c addition_cmd.c)

LIBFT = make -C ./libft
FT_PRINTF = make -C ./ft_printf

NAME = minishell
OBJ_DIR = objects
OBJ_PARSER = $(SRC_PARSER:%.c=$(OBJ_DIR)/%.o)
OBJ_BUILTINS = $(SRC_BUILTINS:%.c=$(OBJ_DIR)/%.o)
OBJ_EXECUTION = $(SRC_EXECUTION:%.c=$(OBJ_DIR)/%.o)
OBJ = $(OBJ_EXECUTION) $(OBJ_PARSER) $(OBJ_BUILTINS) $(OBJ_DIR)/minishell.o

all: $(NAME)

$(NAME): $(OBJ)
	make bonus -C ./libft
	$(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) ${FLAGS} -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C ./libft
	make clean -C ./ft_printf

fclean: clean
	make fclean -C ./libft
	make fclean -C ./ft_printf
	rm -rf $(NAME)

re: fclean all