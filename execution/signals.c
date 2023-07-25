/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:16:57 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 06:39:01 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_sig(void)
{
	if (global_struct.heredoc_signal == 1)
	{
		global_struct.i = open(global_struct.fd, O_RDONLY);
		dup2(global_struct.i, 0);
		return (1);
	}
	return (0);
}

void	sig_here(int signum)
{
	(void)signum;
	global_struct.fd = ttyname(0);
	printf("\n");
	close(0);
	rl_replace_line("", 0);
	rl_on_new_line();
	global_struct.heredoc_signal = 1;
	global_struct.g_exit_status = 1;
}

void	sig_int(int signum)
{
	(void)signum;
	if (global_struct.heredoc_signal == 0)
		printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	global_struct.g_exit_status = 1;
}

void	handle_exit_status(t_pipes_n_redirection *pipes_n_redirection)
{
	if (pipes_n_redirection->exit_builtin)
		global_struct.g_exit_status = 1;
	else if (WIFEXITED(global_struct.g_exit_status))
		global_struct.g_exit_status = WEXITSTATUS(global_struct.g_exit_status);
	else if (WIFSIGNALED(global_struct.g_exit_status))
		global_struct.g_exit_status = WTERMSIG(global_struct.g_exit_status)
			+ 128;
}
