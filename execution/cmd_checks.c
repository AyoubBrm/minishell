/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:11:55 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 11:52:59 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_such_file(t_table *current,
					t_pipes_n_redirection *pipes_n_redirection,
					int i)
{
	struct stat	dir;

	if (!current->cmd)
		exit(0);
	if ((access(current->cmd, F_OK | X_OK) < 0 && current->cmd[0] == '/')
		|| (current->cmd[0] == '.' && access(current->cmd, F_OK | X_OK) < 0))
	{
		if (current->redirection->type[i] && ft_strncmp(
				current->redirection->type[i], "<<", 3) != 0)
		{
			out_redirection(current, pipes_n_redirection, i);
			app_redirection(current, pipes_n_redirection, i);
		}
		ft_printf("bash: %s: No such file or directory\n", current->cmd);
		exit(g_global_struct.g_exit_status = 127);
	}
	no_such_file2(current, pipes_n_redirection, i);
	if (stat(current->cmd, &dir) == 0)
	{
		if (S_ISDIR(dir.st_mode))
		{
			ft_printf("bash: %s: is a directory\n", current->cmd);
			exit(g_global_struct.g_exit_status = 126);
		}
	}
}

int	ambig_check(t_table *current, t_pipes_n_redirection *pipes_n_redirection,
		t_myarg *arg)
{
	if ((current->ambiguous && arg->ex_here) || arg->ambg)
	{
		ft_printf("bash: %s: ambiguous redirect\n", arg->p);
		g_global_struct.g_exit_status = 1;
		destroy(pipes_n_redirection);
		return (1);
	}
	if (current->no_file_dire)
	{
		ft_printf("bash: : No such file or directory\n");
		g_global_struct.g_exit_status = 1;
		destroy(pipes_n_redirection);
		return (1);
	}
	return (0);
}

void	no_such_file2(t_table *current,
					t_pipes_n_redirection *pipes_n_redirection,
					int i)
{
	int		flag;
	int		j;

	if (!current->cmd[0] || (!pipes_n_redirection->cmd && current->cmd[0] != '/'
			&& !is_builtin(current->cmd) && access(current->cmd,
				F_OK | X_OK) < 0))
	{
		if (current->redirection->type[i] && ft_strncmp(
				current->redirection->type[i], "<<", 3) != 0)
		{
			out_redirection(current, pipes_n_redirection, i);
			app_redirection(current, pipes_n_redirection, i);
		}
		j = 0;
		flag = 0;
		no_such_file3(current, pipes_n_redirection, i, &flag);
		if (flag)
		{
			ft_printf("bash: %s: command not found\n", current->cmd);
			exit(g_global_struct.g_exit_status = 127);
		}
		ft_printf("bash: %s: No such file or directory\n", current->cmd);
		exit(g_global_struct.g_exit_status = 127);
	}
}

void	no_such_file3(t_table *current,
					t_pipes_n_redirection *pipes_n_redirection,
					int i, int *flag)
{
	while (pipes_n_redirection->env2d[i])
	{
		if (ft_strnstr(pipes_n_redirection->env2d[i], "PATH", 4))
			*flag = 1;
		i++;
	}
}
