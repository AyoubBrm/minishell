/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/07/19 17:03:50 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_num_pipes(t_table *list)
{
	t_table *current = list;
	int i = 0;

	while (current)
	{
		i += current->pip;
		current = current->next;
	}

	return i;
}

int get_num_heredoc(t_table *list)
{
	t_table *current = list;
	int i = 0;

	while (current)
	{
		i += current->redirection->heredoc;
		current = current->next;
	}
	return i;
}

void magic(t_table *list, t_list **my_en, char **env, t_myarg *arg)
{
	if (!env[0])
		return;
	t_list *my_env;
	my_env = *my_en;
	t_pipes_n_redirection *pipes_n_redirection = ft_calloc(sizeof(t_pipes_n_redirection), 1);

	pipes_n_redirection->env2d = list_to_double_pointer(my_env);
	pipes_n_redirection->path = get_path(pipes_n_redirection->env2d);

	pipes_n_redirection->num_pipes = get_num_pipes(list);
	pipes_n_redirection->pids = ft_calloc(sizeof(int), pipes_n_redirection->num_pipes + 1);
	// if (get_num_heredoc(list))
	// pipes_n_redirection->filenames = ft_calloc(sizeof(char *), get_num_heredoc(list));

	t_table *current_heredoc = list;
	pipes_n_redirection->cmd = NULL;
	pipes_n_redirection->args = NULL;
	pipes_n_redirection->filename = NULL;
	char **p;

	// pipes_n_redirection->filemames = malloc(sizeof(char *) * pipes_n_redirection->num_pipes + 1);
	int x = 0;
	int k = 0;
	t_table *current = list;

	while (current)
	{
		/************************* Handle << redirection (Heredoc) ********************/
		while (current_heredoc)
		{
			pipes_n_redirection->pos_redirection = get_pos_redirection(current->redirection->type, "<<");
			while (x < current->redirection->heredoc)
			{
				pipes_n_redirection->pos_redirection_v2 = get_pos_redirection_v2(pipes_n_redirection->pos_redirection, current_heredoc->redirection->type, "<<");
				pipes_n_redirection->buffer = ft_calloc(1, 1);
				if (current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2])
				{
					free(pipes_n_redirection->filename);
					pipes_n_redirection->filename = ft_strjoin("/tmp/", current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2]);
					// pipes_n_redirection->filenames[x] = pipes_n_redirection->filename;
				}
				if (pipes_n_redirection->tmp)
					close(pipes_n_redirection->tmp);
				if (pipes_n_redirection->in)
					close(pipes_n_redirection->in);

				if (heredoc_which_redirection(current_heredoc->redirection->type) == 1)
					pipes_n_redirection->tmp = open(pipes_n_redirection->filename, O_CREAT | O_RDWR, 0666);
				else if (heredoc_which_redirection(current_heredoc->redirection->type) == 2)
					pipes_n_redirection->tmp = open(pipes_n_redirection->filename, O_CREAT | O_APPEND | O_RDWR, 0666);
				else
					pipes_n_redirection->tmp = open(pipes_n_redirection->filename, O_CREAT | O_RDWR, 0666);
				pipes_n_redirection->in = pipes_n_redirection->tmp;
				while (1)
				{
					pipes_n_redirection->input = readline("> ");
					// printf("%s: %zu: %s: %zu\n", current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2], ft_strlen(current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2]), pipes_n_redirection->input, ft_strlen(pipes_n_redirection->input));
					if (pipes_n_redirection->input && ft_strncmp(pipes_n_redirection->input, current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2], ft_strlen(current_heredoc->redirection->file[pipes_n_redirection->pos_redirection_v2]) + 1) == 0)
					{
						write(pipes_n_redirection->in, pipes_n_redirection->buffer, ft_strlen(pipes_n_redirection->buffer));
						free(pipes_n_redirection->input);
						free(pipes_n_redirection->buffer);
						pipes_n_redirection->pos_redirection++;
						pipes_n_redirection->flag = 1;
						break;
					}
					else if (pipes_n_redirection->input && ft_strchr(pipes_n_redirection->input, '$') && arg->ex_here == 0 && current->exp_heredoc == 0)
					{
						pipes_n_redirection->input = ft_strjoin(pipes_n_redirection->input, "\n");
						p = ft_split_origin(pipes_n_redirection->input, '\n');
						p = expand(p, my_env, arg->num_alloc, arg);
						pipes_n_redirection->input = ft_strdup(p[0]);
					}
					else if (!pipes_n_redirection->input)
						break;
					pipes_n_redirection->tmp_buffer = ft_strjoin(pipes_n_redirection->buffer, pipes_n_redirection->input);
					free(pipes_n_redirection->buffer);
					pipes_n_redirection->buffer = ft_strjoin(pipes_n_redirection->tmp_buffer, "\n");
					free(pipes_n_redirection->tmp_buffer);
					free(pipes_n_redirection->input);
				}
				x++;
			}
			x = 0;
			current_heredoc = current_heredoc->next;
		}
		/************************* End << Heredoc ************************************/

		if ((current->ambiguous && arg->ex_here) || arg->ambg)
		{
			ft_printf("bash: %s: ambiguous redirect\n", arg->p);
			g_exit_status = 1;
			return;
		}
		if (current->no_file_dire)
		{
			ft_printf("bash: : No such file or directory\n");
			g_exit_status = 1;
			return;
		}
		if (pipes_n_redirection->flag && current->cmd && !current->pip)
		{
			close(pipes_n_redirection->in);
			pipes_n_redirection->in = open(pipes_n_redirection->filename, O_RDONLY, 0666);
		}

		/***************************** PIPING *************************/
		pipe(pipes_n_redirection->pipefds);
		pipes_n_redirection->pid = fork();
		if (pipes_n_redirection->pid == 0)
		{
			child(current, pipes_n_redirection, my_env, g_exit_status);
		}
		else
		{
			parent(current, pipes_n_redirection, my_en, g_exit_status);
		}
		// Get all pids
		pipes_n_redirection->pids[k] = pipes_n_redirection->pid;
		k++;

		current = current->next;
	}

	if (pipes_n_redirection->tmp)
		close(pipes_n_redirection->tmp);
	if (pipes_n_redirection->in)
		close(pipes_n_redirection->in);

	free2d(pipes_n_redirection->env2d);
	free2d(pipes_n_redirection->path);

	if (pipes_n_redirection->cmd && pipes_n_redirection->args)
	{
		free2d(pipes_n_redirection->args);
		free(pipes_n_redirection->cmd);
	}
	if (pipes_n_redirection->pipefds[0])
	{
		close(pipes_n_redirection->pipefds[0]);
		close(pipes_n_redirection->pipefds[1]);
	}

	// printf("??\n");
	k = 0;
	// while (k < get_num_heredoc(list))
	// {
	// 	printf("%s\n", pipes_n_redirection->filenames[k]);
	// 	if (pipes_n_redirection->filenames[k])
	// 	{
	// 		unlink(pipes_n_redirection->filenames[k]);
	// 		free(pipes_n_redirection->filenames[k]);
	// 	}
	// 	k++;
	// }
	// free(pipes_n_redirection->filenames);
	if (pipes_n_redirection->flag)
	{
		unlink(pipes_n_redirection->filename);
		free(pipes_n_redirection->filename);
	}

	k = 0;
	while (k < pipes_n_redirection->num_pipes + 1)
	{
		waitpid(pipes_n_redirection->pids[k], &g_exit_status, 0);
		k++;
	}

	free(pipes_n_redirection->pids);
	if (pipes_n_redirection->exit_builtin)
		g_exit_status = 1;
	else
		g_exit_status = WEXITSTATUS(g_exit_status);

	free(pipes_n_redirection);
	// while (1)
	// 	;
}

int heredoc_which_redirection(char **redirection)
{
	int i = 1;

	while (redirection[i])
	{
		if (ft_strncmp(redirection[i], ">", 2) == 0)
			return 1;
		else if (ft_strncmp(redirection[i], ">>", 3) == 0)
			return 2;
		i++;
	}
	return 0;
}

int get_pos_redirection_v2(int start, char **redirection, char *redirection_type)
{
	while (redirection[start])
	{
		if (ft_strncmp(redirection[start], redirection_type, ft_strlen(redirection_type) + 1) == 0)
			return start;
		start++;
	}
	return 0;
}

int get_pos_redirection(char **redirection, char *redirection_type)
{
	int i = 0;
	while (redirection[i])
	{
		if (ft_strncmp(redirection[i], redirection_type, ft_strlen(redirection_type) + 1) == 0)
			return i;
		i++;
	}
	return 0;
}

int is_builtin(char *builtin)
{
	char *built_ins[] = {"env", "export", "echo", "cd", "pwd", "unset", "exit"};
	int i = 0;

	while (i < 7)
	{
		if (ft_strncmp(builtin, built_ins[i], ft_strlen(builtin) + 1) == 0)
			return 1;
		i++;
	}
	return 0;
}
void parser_arg(char *input, char **env, t_list **my_env)
{
	t_table *final_list;
	char **str;
	char **s;
	t_myarg *arg;

	arg = malloc(1 * sizeof(t_myarg));
	arg->quote = 0;
	arg->num_alloc = 0;
	here_doc_expaand(input, arg);
	account_quote(input, arg);
	arg->num_alloc = num_alloc_str(input);
	if (arg->quote % 2 == 1)
	{
		ft_printf("%s\n",
			   "minishell: unexpected EOF while looking for matching");
		g_exit_status = 2;
	}
	else
	{
		str = ft_split(input, '\"');
		s = ft_calloc(sizeof(char *), arg->num_alloc + 1);
		arg->x = 0;
		arg->i = 0;
		arg->index = 0;
		arg->space = 0;
		arg->ambg = 0;
		s = get_token_from_str(str, s, arg);
		arg->final_expand = expand(s, *my_env, arg->num_alloc, arg);
		arg->final_expand = clean_expand(arg->final_expand, "\3\4\5\6", arg);
		final_list = final_addition(arg->final_expand, arg);
		if (final_list == NULL)
			return;
		final_list->exp_exit = arg->exp_exit;		// *******this for expand the exit status if 1 don't (if 0 expand) *******//
		final_list->exp_heredoc = arg->exp_heredoc; // *******this for expand inside heredoc status if 1 don't (if 0 expand)*******//
		// printf("---%d--dasda-\n", arg->exp_exit);
		magic(final_list, my_env, env, arg);
	}
	// int x = 0;
	// while (final_list)
	// {
	// 	printf("********************* BEGIN ***************************\n");
	// 	printf("_____CMD_____=..%s\n\n", final_list->cmd);
	// 	x = 0;
	// 	while (final_list->arg[x])
	// 		printf("_____ARG_____=..%s\n\n", final_list->arg[x++]);
	// 	printf("_____PIPE_____=..%s\n\n", final_list->redirection->pipe);
	// 	x = 0;
	// 	while (final_list->redirection->type[x])
	// 		printf("_____TYPE_REDI_____=..%s\n\n", final_list->redirection->type[x++]);
	// 	x = 0;
	// 	while (final_list->redirection->file[x])
	// 		printf("_____FILE_____=..%s\n\n", final_list->redirection->file[x++]);
	// 	final_list = final_list->next;
	// }
}

void sig_int()
{
	// rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return;
}

int main(int ac, char **av, char **env)
{
	char *input;

	(void)av;
	t_list *my_env = NULL;
	if (ac != 1)
		return (1);
	my_env = get_env(env);
	g_exit_status = 0;
	while (1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		add_history(input);
		if (input)
			parser_arg(input, env, &my_env);
		free(input);
		if (!input)
			return (g_exit_status);
	}
	return (0);
}