/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:46:51 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	out_redirection(t_table *current,
						t_pipes_n_redirection *pipes_n_redirection,
						int i)
{
	pipes_n_redirection->trunc_redirect = open(current->redirection->file[i],
			O_CREAT | O_TRUNC | O_RDWR,
			0666);
	if (pipes_n_redirection->trunc_redirect < 0
		&& current->redirection->file[i])
	{
		ft_printf("bash: %s: Permission denied\n",
			current->redirection->file[i]);
		g_global_struct.g_exit_status = 1;
		exit(g_global_struct.g_exit_status);
	}
	dup2(pipes_n_redirection->trunc_redirect, 1);
	close(pipes_n_redirection->trunc_redirect);
}

void	app_redirection(t_table *current,
						t_pipes_n_redirection *pipes_n_redirection,
						int i)
{
	pipes_n_redirection->append_redirection = open(
			current->redirection->file[i],
			O_CREAT | O_APPEND | O_RDWR,
			0666);
	if (pipes_n_redirection->append_redirection < 0
		&& current->redirection->file[i])
	{
		ft_printf("bash: %s: Permission denied\n",
			current->redirection->file[i]);
		g_global_struct.g_exit_status = 1;
		exit(g_global_struct.g_exit_status);
	}
	dup2(pipes_n_redirection->append_redirection, 1);
	close(pipes_n_redirection->append_redirection);
}

void	in_redirection(t_table *current,
					t_pipes_n_redirection *pipes_n_redirection,
					int i)
{
	if (access(current->redirection->file[i], F_OK) < 0)
	{
		ft_printf("bash: %s: No such file or directory\n",
			current->redirection->file[i]);
		exit(1);
	}
	else if (access(current->redirection->file[i], R_OK) < 0)
	{
		ft_printf("bash: %s: Permission denied\n",
			current->redirection->file[i]);
		exit(1);
	}
	else
	{
		pipes_n_redirection->tmp = open(current->redirection->file[i], O_RDONLY,
				0666);
		dup2(pipes_n_redirection->tmp, 0);
		close(pipes_n_redirection->tmp);
		if (current->pip)
			dup2(pipes_n_redirection->pipefds[1], 1);
	}
}

void	all_redirections(t_table *current,
						t_pipes_n_redirection *pipes_n_redirection)
{
	int		i;

	i = 0;
	while (i < current->redirection->how_many)
	{
		if (ft_strncmp(current->redirection->type[i], ">", 2) == 0)
			out_redirection(current, pipes_n_redirection, i);
		else if (ft_strncmp(current->redirection->type[i], ">>", 3) == 0)
			app_redirection(current, pipes_n_redirection, i);
		else if (ft_strncmp(current->redirection->type[i], "<", 2) == 0)
			in_redirection(current, pipes_n_redirection, i);
		i++;
	}
	if (!current->cmd)
		exit(0);
}
