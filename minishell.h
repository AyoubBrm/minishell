/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 16:40:27 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>

void	rl_replace_line(const char *text, int clear_undo);

typedef struct g_gl
{
	int				g_exit_status;
	int				heredoc_signal;
	char			*fd;
	int				i;
}					t_global;

t_global			g_global_struct;

typedef struct s_myenv
{
	char			*key;
	char			*value;
	struct s_myenv	*next;
}					t_myenv;

typedef struct s_env
{
	char			*pwd;
}					t_env;

typedef struct s_addition
{
	int				how_many;
	int				heredoc;
	int				out_redirection;
	int				in_redirection;
	int				append_redirection;
	char			**type;
	char			**file;
	char			*pipe;

}					t_redirection;

typedef struct s_tab
{
	int				pip;
	int				num_pipes;
	char			*cmd;
	t_redirection	*redirection;
	char			**arg;
	struct s_tab	*next;
	int				ambiguous;
	int				no_file_dire;
	int				exp_exit;
	int				exp_heredoc;
	int				x;
}					t_table;

typedef struct s_my
{
	int				x;
	int				i;
	int				index;
	int				num_alloc;
	int				quote;
	int				exp_heredoc;
	int				exp_exit;
	char			**final_expand;
	char			**str_new;
	int				star;
	char			*var;
	char			*temp_expand;
	char			**ex_env;
	char			*temp_str;
	char			*temp;
	char			*p;
	int				ex_here;
	int				space;
	int				ambg;
	char			*tmp;
	int				indx;
	char			*input;
}					t_myarg;

typedef struct pipes_n_redirection
{
	char			**env2d;
	int				heredoc;
	char			**path;
	char			*input;
	int				tmp;
	int				trunc_redirect;
	int				append_redirection;
	int				pos_redirection;
	int				pos_redirection_v2;
	char			*buffer;
	char			*tmp_buffer;
	int				*pids;
	int				num_pipes;
	char			*cmd;
	char			**args;
	char			*filename;
	char			**filenames;
	int				pipefds[2];
	int				in;
	int				out;
	int				pid;
	int				flag;
	int				abs_path;
	int				is_redirected;
	int				exit_builtin;
	char			wildcard[200];
}					t_pipes_n_redirection;

typedef struct s_my_export
{
	int				lol;
	int				offset;
	int				equal;
	int				i;
	char			*key;
	char			*value;
}					t_my_export;

/******************************** INIT **************************/
int		init(char *input, t_list *my_env);

void	parser_arg(char *input, t_list **my_env);
void	pars_pipe_and_rid(char **str, char **s, t_myarg *arg);
char	**get_token_from_str(char **str, char **s, t_myarg *arg);
void	check_ambig(t_list *my_env, t_myarg *arg, char **s);
void	account_quote(char *input, t_myarg *arg);
char	**clean_expand(char **final_expand, char *str, t_myarg *arg);
void	token_v2(char **str, char **s, t_myarg *arg);
void	free_list(t_table *head);
void	str_and_dollar_with_out_quote(char **str, char **s, t_myarg *arg);
char	**join2d_with_arr(char **str1, char *str2);
void	free_list(t_table *head);
t_table	*error(t_table *list);
void	ambiguous_no_file(t_table *head, t_myarg *arg);
int		num_alloc_str(char *input);
char	**join_2d_arr(char **str1, char **str2);
void	here_doc_expaand(char *input, t_myarg *arg);
void	str_inside_double_qoute(char **str, char **s, t_myarg *arg);
void	str_inside_single_qoute(char **str, char **s, t_myarg *arg);
void	pars_pipe_and_rid(char **str, char **s, t_myarg *arg);

char	*find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand,
			int flags);
void	addition_cmd(char **str_new, int *i, t_table *new_addition);
int		get_pos_redirection_v2(int start, char **redirection,
			char *redirection_type);
char	**expand(char **s, t_list *my_env, int num_alloc, t_myarg *arg);
void	expand_inside_env_or_dont_expand(t_list *my_env, t_myarg *arg,
			char **s);
t_table	*final_addition(char **str_new, t_myarg *arg);
t_table	*addition_infile(char **str_new, int *i, t_table *new_addition);
t_table	*addition_part(char **str_new, t_table *new_addition);
t_table	*output_rid_and_cmd(char **str_new, int *i, t_table *new_addition);
void	token_without_quotev2(char **str, char **s, t_myarg *arg, int star);

/******************************** Builtins echo **************************/
void	my_echo(char **cmd);
int		handle_n(char *args);
void	handle_n_helper(int i, char **cmd, int *flag);
void	echo_check(char **cmd, int i, int *flag, int *blank);

/******************************** Builtins pwd **************************/
void	my_pwd(void);

/******************************** Builtins cd **************************/
int		my_cd(char *path, t_list *myenv,
			t_pipes_n_redirection *pipes_n_redirection);
int		cd_check(char *path, int *home_found, t_list *current);
void	cd_find_home(t_list *current);

/******************************** Builtins exit **************************/
int		my_exit(char **args, t_pipes_n_redirection *pipes_n_redirection);
void	exit_check(char **args, int i, int j);
int		exit_check2(char **args, int overflow);

/******************************** Builtins unset **************************/
void	my_unset(char **to_unset, t_list **my_env);
void	unset_helper(t_list **my_env, t_list *current, t_list *tmp,
			char *to_unset);

/******************************** Builtins env **************************/
t_list	*get_env(char **env);
void	my_env(char **env, char **cmd, t_env *myenv);
void	new_env(t_list **head);
void	env_alloc(t_list **new_env, char **env_old, char *envi);

/******************************** Builtins export **************************/
int		check_myexport(char *cmd, int i);
int		get_equal_pos(char *key);
void	myexport(char **cmd, t_list *my_env,
			t_pipes_n_redirection *pipes_n_redirection);
void	my_export_add(char *cmd, t_list *my_env);
void	my_export_alloc(t_list **my_export, t_list *current, int b, int k);
int		my_export_check2(char *cmd, t_pipes_n_redirection *pipes_n_redirection);
void	print_export(char **cmd, t_list *my_env);
int		my_export_check3(t_pipes_n_redirection *pipes_n_redirection, char *cmd,
			int *flag, int j);
void	my_export_add2(t_my_export *my_export, char *cmd, t_list *new_export,
			t_list *my_env);
void	my_export_add3(t_list *current, char *key, char *value, char *cmd);
void	my_export_alloc2(t_list **new_export, t_list **my_env,
			t_my_export my_export, char *cmd);
void	free_and_alloc_export(char *cmd, t_my_export *my_export,
			t_list *current);

/******************************** EXECUTION **************************/
void	magic(t_table *list, t_list **my_en, t_myarg *arg);
//Init Pointers
void	init_p(t_pipes_n_redirection *pipes_n_redirection);
void	get_utils(t_pipes_n_redirection *pipes_n_redirection, t_table *list,
			t_list *my_env);
int		get_num_pipes(t_table *list);
void	exec_pipes(t_pipes_n_redirection *pipes_n_redirection, t_table *current,
			t_list **my_en, t_list *my_env);
void	which_cmd_type(t_pipes_n_redirection *pipes_n_redirection,
			t_table *current);
void	close_fds(t_pipes_n_redirection *pipes_n_redirection);
void	wait_for_children(t_pipes_n_redirection *pipes_n_redirection);
void	execute_cmds(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, t_list *my_env);
void	child(t_table *current, t_pipes_n_redirection *pipes_n_redirection,
			t_list *my_env);
void	parent(t_table *current, t_pipes_n_redirection *pipes_n_redirection,
			t_list **my_env);
//Check errors
int		ambig_check(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, t_myarg *arg);
void	exec_helper(t_pipes_n_redirection *pipes_n_redirection);
void	no_such_file2(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection,
			int i);
void	no_such_file3(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection,
			int i, int *flag);
//Free
void	destroy(t_pipes_n_redirection *pipes_n_redirection);
void	free2d(char **arg);
void	free_env(void *env);
void	freenode(t_list **lst, t_list *node);

/******************************** REDIRECTIONS **************************/
void	no_such_file(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, int i);
void	all_redirections(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection);
int		get_num_heredoc(t_table *list);
int		heredoc_which_redirection(char **redirection);
int		get_pos_redirection(char **redirection, char *redirection_type);
int		get_pos_redirection_v2(int start, char **redirection,
			char *redirection_type);
void	out_redirection(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, int i);
void	app_redirection(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, int i);
void	in_redirection(t_table *current,
			t_pipes_n_redirection *pipes_n_redirection, int i);

void	heredoc(t_table *list, t_list *my_env, t_myarg *arg,
			t_pipes_n_redirection *pipes_n_redirection);
int		heredoc_utils(t_pipes_n_redirection *pipes_n_redirection,
			t_table *current_heredoc);
int		heredoc_utils2(t_pipes_n_redirection *pipes_n_redirection,
			t_table *current_heredoc, t_myarg *arg, t_list *my_env);
int		heredoc_utils3(t_pipes_n_redirection *pipes_n_redirection);
void	heredoc_join_n_write(t_pipes_n_redirection *pipes_n_redirection);
void	heredoc_loop(t_pipes_n_redirection *pipes_n_redirection,
			t_table *current_heredoc, t_myarg *arg, t_list *my_env);
int		heredoc_main(t_pipes_n_redirection *pipes_n_redirection,
			t_table *current_heredoc, t_myarg *arg, t_list *my_env);

void	handle_exit_status(t_pipes_n_redirection *pipes_n_redirection);

//Signals
void	sig_here(int signum);
int		heredoc_sig(void);
void	sig_int(int signum);

/******************************** UTILS **************************/
char	**get_path(char **env);
char	**list_to_double_pointer(t_list *my_env);
char	*check_valid_cmd(char *cmd, char **path);
char	**copy_args_to_2d(char *cmd_path, char **args);
int		is_builtin(char *builtin);
#endif