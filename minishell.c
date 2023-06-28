/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/06/26 23:35:40 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int g_exit_status;
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

int magic(t_table *list, t_list *my_env, char **env, t_list *next)
{
	(void)env;
	// next = my_env->next;
	char **env2d = list_to_double_pointer(my_env, next);
	char **path = get_path(env2d);

	// while(path[i])
	// {
	// 	printf("%s\n", path[i]);
	// 	i++;
	// }
	t_table *current = list;
	// t_table *current_heredoc = list;
	char *input;
	int tmp; // Open tmp file for heredoc
	int trunc_redirect;
	int append_redirection;
	int pos_redirection;
	int pos_redirection_v2;
	char *buffer = NULL; // tmp string to join input of heredoc
	int x = 0;
	char *cmd = NULL;
	char **args = NULL;
	char *filename;
	int j = 0;
	int pipefds[2];
	int in = 0; // Save input of the previous cmd
	int out = 0;
	int pid = 0;
	int flag = 0;
	int abs_path = 0;
	int num_pipes = get_num_pipes(list);
	int exit_st;

	t_table *current_heredoc = list;

	while (current)
	{
		// !!!!!!!!!!!!!!!!!!!!!To check later!!!!!!!!!!
		if (current->cmd)
		{
			cmd = check_valid_cmd(current->cmd, path);
			args = copy_args_to_2d(current->cmd, current->arg);
			while (args[j])
			{
				// printf("args: %s\n", args[j]);
				j++;
			}
			j = 0;
		}

		/************************* Handle << redirection (Heredoc) ********************/
		while (current_heredoc)
		{
			pos_redirection = get_pos_redirection(current->redirection->type, "<<");
			while (x < current_heredoc->redirection->heredoc)
			{
				pos_redirection_v2 = get_pos_redirection_v2(pos_redirection, current_heredoc->redirection->type, "<<");
				buffer = ft_calloc(1, 1);
				filename = ft_calloc(1, 1);
				if (current_heredoc->redirection->file[pos_redirection_v2])
					filename = ft_strjoin("/tmp/", current_heredoc->redirection->file[pos_redirection_v2]);
				tmp = open(filename, O_CREAT | O_RDWR, 0666);
				printf("Stopping word: %s\n", current_heredoc->redirection->file[pos_redirection_v2]);
				in = dup(tmp);
				// dup2(tmp, 0);
				while (1)
				{
					input = readline("> ");
					// printf("buf %s\n", buffer);
					if (ft_strncmp(input, current_heredoc->redirection->file[pos_redirection_v2], ft_strlen(current_heredoc->redirection->file[pos_redirection_v2]) + 1) == 0)
					{
						write(in, buffer, ft_strlen(buffer));
						free(input);
						free(buffer);
						pos_redirection++;
						flag = 1;
						break;
					}
					buffer = ft_strjoin(buffer, input);
					buffer = ft_strjoin(buffer, "\n");
					free(input);
					// free(buffer);
				}
				x++;
			}
			x = 0;
			current_heredoc = current_heredoc->next;
		}
		/***************************** PIPING *************************/
		pipe(pipefds);
		if (current->cmd)
		{
			pid = fork();
			if (pid == 0)
			{
				/************************* Check for cmd permissions and existence ********************/
				if (current->cmd && ((access(current->cmd, F_OK) < 0 && current->cmd[0] == '/') || (current->cmd[0] == '.' && access(current->cmd, F_OK | X_OK) < 0)))
				{
					printf("minishell: %s: No such file or directory\n", current->cmd);
					g_exit_status = 127;
					exit(g_exit_status);
				}
				else if (!cmd && current->cmd[0] != '/' && !is_builtin(current->cmd) && access(current->cmd, F_OK | X_OK) < 0)
				{
					printf("minishell: %s: command not found\n", current->cmd);
					g_exit_status = 127;
					exit(g_exit_status);
				}
				else
				{
					if (access(current->cmd, F_OK | X_OK) == 0)
						abs_path = 1;
					dup2(in, 0);
					if (current->pip)
						dup2(pipefds[1], 1);
					close(pipefds[0]);
					close(pipefds[1]);
					/************************* Handle > redirection ********************/
					x = 0;
					pos_redirection = get_pos_redirection(current->redirection->type, ">");
					while (x < current->redirection->out_redirection)
					{
						pos_redirection_v2 = get_pos_redirection_v2(pos_redirection, current->redirection->type, ">");
						if (current->redirection->file[pos_redirection_v2] && ft_strncmp(current->redirection->type[pos_redirection_v2], ">", 2) == 0)
						{
							trunc_redirect = open(current->redirection->file[pos_redirection_v2], O_CREAT | O_TRUNC | O_RDWR, 0666);
							out = dup(1);
							dup2(trunc_redirect, 1);
							close(trunc_redirect);
							pos_redirection++;
						}
						x++;
					}
					/************************* Handle < redirection ********************/
					// printf("current->ambiguous %d\n", current->ambiguous);

					x = 0;
					pos_redirection = get_pos_redirection(current->redirection->type, "<");
					while (x < current->redirection->in_redirection)
					{
						pos_redirection_v2 = get_pos_redirection_v2(pos_redirection, current->redirection->type, "<");
						if (ft_strncmp(current->redirection->type[pos_redirection_v2], "<", 2) == 0)
						{
							if (access(current->redirection->file[pos_redirection_v2], F_OK) < 0)
							{
								printf("minishell: %s: No such file or directory\n", current->redirection->file[pos_redirection_v2]);
								return (1);
							}
							else
							{
								tmp = open(current->redirection->file[pos_redirection_v2], O_RDONLY, 0666);
								args = copy_args_to_2d(current->cmd, current->arg);
								execve(cmd, args, env2d);
							}
							pos_redirection++;
						}
						x++;
					}
					if (flag && current->cmd && !current->pip)
					{
						// printf("WTF redire %s => %d\n", current->cmd, current->pip);
						in = open(filename, O_RDONLY, 0666);
					}
					/************************* Handle >> redirection ********************/
					x = 0;
					pos_redirection = get_pos_redirection(current->redirection->type, ">>");
					while (x < current->redirection->append_redirection)
					{
						pos_redirection_v2 = get_pos_redirection_v2(pos_redirection, current->redirection->type, ">>");
						if (current->redirection->file[pos_redirection_v2] && ft_strncmp(current->redirection->type[pos_redirection_v2], ">>", 2) == 0)
						{
							append_redirection = open(current->redirection->file[pos_redirection_v2], O_CREAT | O_APPEND | O_RDWR, 0666);
							out = dup(1);
							dup2(append_redirection, 1);
							close(append_redirection);
							pos_redirection++;
						}
						x++;
					}
					if (is_builtin(current->cmd))
					{
						if (current->cmd && !current->arg[0] && ft_strncmp(current->cmd, "export", 7) == 0)
							myexport(current->arg, my_env);
						else if (current->cmd && ft_strncmp(current->cmd, "env", 4) == 0)
							new_env(my_env);
						else if (current->cmd && ft_strncmp(current->cmd, "echo", 5) == 0)
							my_echo(current->arg, g_exit_status);
						else if (current->cmd && ft_strncmp(current->cmd, "pwd", 4) == 0)
							my_pwd();
						// exit(0);
					}
					else
					{
						if (!abs_path)
							execve(cmd, args, env2d);
						else
							execve(current->cmd, args, env2d);
					}
					exit(0);
				}
			}
			else
			{
				if (current->cmd && current->arg[0] && ft_strncmp(current->cmd, "export", 7) == 0)
					myexport(current->arg, my_env);
				else if (current->cmd && ft_strncmp(current->cmd, "unset", 6) == 0)
					my_unset(current->arg, my_env, next);
				else if (current->cmd && ft_strncmp(current->cmd, "exit", 5) == 0)
				{
					if (!num_pipes)
						my_exit(current->arg, g_exit_status);
				}
				else if (current->cmd && ft_strncmp(current->cmd, "cd", 3) == 0)
				{
					if (!num_pipes)
						my_cd(current->arg[0], my_env);
				}
				close(pipefds[1]);
				// close(1);
				in = dup(pipefds[0]); // Save input of the previous cmd
				close(pipefds[0]);
				dup2(out, 1);
			}
		}

		if (cmd && args)
		{
			free2d(args);
			free(cmd);
		}
		current = current->next;
	}
	// close(in);
	close(pipefds[0]);
	close(pipefds[1]);
	// printf("here??");
	// dup2(in, 0);
	if (flag)
	{
		unlink(filename);
	}
	waitpid(pid, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
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
		{
			// printf("\n--builtin %s\n", builtin);
			return 1;
		}
		i++;
	}
	return 0;
}
void	parser_arg(char *input, char **env, t_list *my_env, t_list *next)
{
	t_table	*final_list;
	char	**str;
	char	**s;
	t_myarg	*arg;

	arg = malloc(1 * sizeof(t_myarg));
	arg->quote = 0;
	arg->num_alloc = 0;
	here_doc_expaand(input, arg);
	account_quote(input, arg);
	arg->num_alloc = num_alloc_str(input);
	if (arg->quote % 2 == 1)
		printf("%s\n",
			"minishell: syntax error near unexpected token `\"' or `\''");
	else
	{
		str = ft_split(input, '\"');
		s = ft_calloc(sizeof(char *), arg->num_alloc + 1);
		arg->x = 0;
		arg->i = 0;
		arg->index = 0;
		s = get_token_from_str(str, s, arg);
		arg->final_expand = expand(s, my_env, arg->num_alloc, arg);
		arg->final_expand = clean_expand(arg->final_expand, "\3\4\5\6", arg);
		final_list = final_addition(arg->final_expand);
		if (final_list == NULL)
			return;
		final_list->exp_exit = arg->exp_exit; // *******this for expand the exit status if 1 don't (if 0 expand) *******//
		final_list->exp_heredoc = arg->exp_heredoc;// *******this for expand inside heredoc status if 1 don't (if 0 expand)*******//
		magic(final_list, my_env, env, next);
	}
	int x = 0;
		while (final_list)
		{
			printf("********************* BEGIN ***************************\n");
			printf("_____CMD_____=..%s\n\n", final_list->cmd);
			x = 0;
			while (final_list->arg[x])
				printf("_____ARG_____=..%s\n\n", final_list->arg[x++]);
			printf("_____PIPE_____=..%s\n\n", final_list->redirection->pipe);
			x = 0;
			while (final_list->redirection->type[x])
				printf("_____TYPE_REDI_____=..%s\n\n", final_list->redirection->type[x++]);
			x = 0;
			while (final_list->redirection->file[x])
				printf("_____FILE_____=..%s\n\n", final_list->redirection->file[x++]);
			final_list = final_list->next;
		}
}

void	sig_int()
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int main(int ac, char **av, char **env)
{
	char *input;

	(void)av;
	t_list *my_env = NULL;
	t_list *next;
	if (ac != 1)
		return (1);
	my_env = get_env(env);
	next = my_env->next;
	g_exit_status = 0;
	while (1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		add_history(input);
		if (input)
			parser_arg(input, env, my_env, next);
		free(input);
		if (!input)
			return (0);
	}
	return (0);
}
