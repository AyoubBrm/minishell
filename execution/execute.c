/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 07:48:25 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_valid_cmd(char *cmd, char **path)
{
	int		i;
	char	*valid_path;
	char	*valid_cmd;

	i = 0;
	while (path && path[i])
	{
		valid_path = ft_strjoin_no_free(path[i], "/");
		if (cmd)
			valid_cmd = ft_strjoin_no_free(valid_path, cmd);
		if (access(valid_cmd, F_OK) == 0)
		{
			free(valid_path);
			return (valid_cmd);
		}
		if (cmd)
			free(valid_cmd);
		free(valid_path);
		i++;
	}
	return (0);
}

void	execute_cmds(t_table *current,
					t_pipes_n_redirection *pipes_n_redirection,
					t_list *my_env)
{
	if (is_builtin(current->cmd))
	{
		if (current->cmd && !current->arg[0] && ft_strncmp(current->cmd,
				"export", 7) == 0)
			myexport(current->arg, my_env, pipes_n_redirection);
		else if (current->cmd && ft_strncmp(current->cmd, "env", 4) == 0)
			new_env(&my_env);
		else if (current->cmd && ft_strncmp(current->cmd, "echo", 5) == 0)
			my_echo(current->arg);
		else if (current->cmd && ft_strncmp(current->cmd, "pwd", 4) == 0)
			my_pwd();
	}
	else
		which_cmd_type(pipes_n_redirection, current);
	exit(0);
}

void	child(t_table *current, t_pipes_n_redirection *pipes_n_redirection,
		t_list *my_env)
{
	int	i;

	i = 0;
	all_redirections(current, pipes_n_redirection);
	if (current->cmd || current->cmd[0])
	{
		free(pipes_n_redirection->cmd);
		free2d(pipes_n_redirection->args);
		pipes_n_redirection->cmd = check_valid_cmd(current->cmd,
				pipes_n_redirection->path);
		pipes_n_redirection->args = copy_args_to_2d(current->cmd, current->arg);
	}
	no_such_file(current, pipes_n_redirection, i);
	if (access(current->cmd, F_OK | X_OK) == 0)
		pipes_n_redirection->abs_path = 1;
	dup2(pipes_n_redirection->in, 0);
	if (current->pip)
	{
		dup2(pipes_n_redirection->pipefds[1], 1);
		close(pipes_n_redirection->pipefds[0]);
		close(pipes_n_redirection->pipefds[1]);
	}
	all_redirections(current, pipes_n_redirection);
	execute_cmds(current, pipes_n_redirection, my_env);
}

void	parent(t_table *current, t_pipes_n_redirection *pipes_n_redirection,
		t_list **my_env)
{
	if (current->cmd && current->arg[0] && ft_strncmp(current->cmd, "export",
			7) == 0)
		myexport(current->arg, *my_env, pipes_n_redirection);
	else if (current->cmd && ft_strncmp(current->cmd, "unset", 6) == 0
		&& !current->pip)
	{
		my_unset(current->arg, my_env);
	}
	else if (current->cmd && ft_strncmp(current->cmd, "exit", 5) == 0)
	{
		if (!pipes_n_redirection->num_pipes)
			my_exit(current->arg, pipes_n_redirection);
	}
	else if (current->cmd && ft_strncmp(current->cmd, "cd", 3) == 0)
	{
		if (!pipes_n_redirection->num_pipes)
			my_cd(current->arg[0], *my_env, pipes_n_redirection);
	}
	close(pipes_n_redirection->pipefds[1]);
	if (pipes_n_redirection->in != 0)
		close(pipes_n_redirection->in);
	pipes_n_redirection->in = pipes_n_redirection->pipefds[0];
}
