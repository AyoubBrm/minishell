/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:16:57 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:27:08 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_sig(void)
{
	if (g_global_struct.heredoc_signal == 1)
	{
		g_global_struct.i = open(g_global_struct.fd, O_RDONLY);
		dup2(g_global_struct.i, 0);
		return (1);
	}
	return (0);
}

void	sig_here(int signum)
{
	(void)signum;
	g_global_struct.fd = ttyname(0);
	printf("\n");
	close(0);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_global_struct.heredoc_signal = 1;
	g_global_struct.g_exit_status = 1;
}

void	sig_int(int signum)
{
	(void)signum;
	if (g_global_struct.heredoc_signal == 0)
		printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global_struct.g_exit_status = 1;
}

void	handle_exit_status(t_pipes_n_redirection *pipes_n_redirection)
{
	if (pipes_n_redirection->exit_builtin)
		g_global_struct.g_exit_status = 1;
	else if (WIFEXITED(g_global_struct.g_exit_status))
		g_global_struct.g_exit_status = WEXITSTATUS(
				g_global_struct.g_exit_status);
	else if (WIFSIGNALED(g_global_struct.g_exit_status))
		g_global_struct.g_exit_status = WTERMSIG(g_global_struct.g_exit_status)
			+ 128;
}
