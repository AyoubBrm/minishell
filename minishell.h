/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/06/27 23:15:49 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <signal.h>
#include <sys/errno.h>
#include <fcntl.h>

typedef struct s_myenv
{
    char *key;
    char *value;
    struct s_myenv *next;
}   t_myenv;

typedef struct s_env
{
    char *pwd;
    // char **myenv;
}   t_env;

void *my_realloc(char *ptr, int size);
// Built-ins
void my_echo(char **cmd, int exit_status);
int handle_n(char *args);
void my_cd(char *path, t_list *myenv);
char *my_pwd();
void my_env(char **env, char **cmd, t_env *myenv);
t_list *get_env(char **env);
void new_env(t_list *head);
int my_exit(char **args, int exit_status);
void myexport(char **cmd, t_list *my_env);

void my_unset(char **to_unset, t_list *my_env, t_list *next);

// Free
void free2d(char **arg);
void free_env(void *env);
void freenode(t_list **lst, t_list *node);

//barssing

typedef struct s_addition
{
	int how_many;
	int heredoc;
	int out_redirection;
	int in_redirection;
	int append_redirection;
	char **type;
	char **file;
	char *pipe;
	
}t_redirection;

typedef struct s_tab
{
	int pip;
	int num_pipes;
	char *cmd;
	t_redirection *redirection;
	char **arg;
	struct s_tab *next;
	int ambiguous;
	int no_file_dire;
	int exp_exit;
	int exp_heredoc;
	int	x;
}t_table;

typedef struct s_my
{
	int		x;
	int		i;
	int		index;
	int		num_alloc;
	int		quote;
	int		exp_heredoc;
	int		exp_exit;
	char	**final_expand;
	char	**str_new;
	int		star;
	char	*var;
	char	*temp_expand;
	char	**ex_env;
	char	*temp_str;
	char	*temp;
}t_myarg;


char	**get_token_from_str(char **str, char **s, t_myarg *arg);
void	account_quote(char *input, t_myarg *arg);
char	**clean_expand(char **final_expand, char *str, t_myarg *arg);
void	token_v2(char **str, char **s, t_myarg *arg);
void	free_list(t_table *head);
void	str_and_dollar_with_out_quote(char **str, char**s, t_myarg *arg);
char	**join2d_with_arr(char **str1, char *str2);
void	free_list(t_table *head);
t_table	*error(t_table *list);
void	ambiguous_no_file(t_table *head);
int		num_alloc_str(char *input);
char	**join_2d_arr(char **str1, char **str2);
void	here_doc_expaand(char *input, t_myarg *arg);
void	str_inside_double_qoute(char **str, char **s, t_myarg *arg);
void	str_inside_single_qoute(char **str, char **s, t_myarg *arg);
char 	**get_path(char **env);
char 	**list_to_double_pointer(t_list *my_env, t_list *next);
char 	*check_valid_cmd(char *cmd, char **path);
char 	**copy_args_to_2d(char *cmd_path, char **args);
void 	pipes(t_table *list, char **args, char **env2d, char *cmd);
int 	is_builtin(char *builtin);
char 	**copy_args_to_2d_redirection(char *filename, char *cmd_path);
int 	get_pos_redirection(char **redirection, char *redirection_type);
char	*find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand,
		int flags);
int 	get_pos_redirection_v2(int start, char **redirection, char *redirection_type);
char	**expand(char **s, t_list *my_env, int num_alloc, t_myarg *arg);
void	expand_inside_env_or_dont_expand(t_myarg *arg);
t_table	*final_addition(char **str_new);
t_table *addition_infile(char **str_new, int *i, t_table *new_addition);
t_table *addition_part(char **str_new, t_table *new_addition);
t_table	*output_rid_and_cmd(char **str_new, int *i, t_table *new_addition);



#endif