/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:57:23 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 18:49:17 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_pipes_n_redirection *pipes_n_redirection, t_table *current,
		t_list **my_en, t_list *my_env)
{
	pipe(pipes_n_redirection->pipefds);
	signal(SIGINT, SIG_IGN);
	pipes_n_redirection->pid = fork();
	if (pipes_n_redirection->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child(current, pipes_n_redirection, my_env);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		parent(current, pipes_n_redirection, my_en);
	}
}

void	wait_for_children(t_pipes_n_redirection *pipes_n_redirection)
{
	int	i;

	i = 0;
	while (i < pipes_n_redirection->num_pipes + 1)
	{
		waitpid(pipes_n_redirection->pids[i],
			&g_global_struct.g_exit_status, 0);
		i++;
	}
}

void	close_fds(t_pipes_n_redirection *pipes_n_redirection)
{
	if (pipes_n_redirection->in)
		close(pipes_n_redirection->in);
	if (pipes_n_redirection->pipefds[0])
	{
		close(pipes_n_redirection->pipefds[0]);
		close(pipes_n_redirection->pipefds[1]);
	}
	if (pipes_n_redirection->flag)
		unlink(pipes_n_redirection->filename);
}

void	heredoc(t_table *list, t_list *my_env, t_myarg *arg,
		t_pipes_n_redirection *pipes_n_redirection)
{
	t_table	*current_heredoc;
	int		i;

	current_heredoc = list;
	i = 0;
	while (current_heredoc)
	{
		pipes_n_redirection->pos_redirection = get_pos_redirection(
				current_heredoc->redirection->type,
				"<<");
		while (i < current_heredoc->redirection->heredoc)
		{
			heredoc_main(pipes_n_redirection, current_heredoc, arg, my_env);
			i++;
		}
		i = 0;
		current_heredoc = current_heredoc->next;
	}
	pipes_n_redirection->heredoc = 0;
}

int	heredoc_main(t_pipes_n_redirection *pipes_n_redirection,
		t_table *current_heredoc, t_myarg *arg, t_list *my_env)
{
	pipes_n_redirection->pos_redirection_v2 = get_pos_redirection_v2(
			pipes_n_redirection->pos_redirection,
			current_heredoc->redirection->type, "<<");
	pipes_n_redirection->buffer = ft_calloc(1, 1);
	if (current_heredoc->redirection->file
		[pipes_n_redirection->pos_redirection_v2])
	{
		free(pipes_n_redirection->filename);
		pipes_n_redirection->filename = ft_strjoin_no_free("/tmp/",
				current_heredoc->redirection->file
			[pipes_n_redirection->pos_redirection_v2]);
	}
	if (pipes_n_redirection->in)
		close(pipes_n_redirection->in);
	pipes_n_redirection->in = open(pipes_n_redirection->filename,
			O_CREAT | O_RDWR,
			0666);
	heredoc_loop(pipes_n_redirection, current_heredoc, arg, my_env);
	if (g_global_struct.heredoc_signal == 1)
	{
		g_global_struct.i = open(g_global_struct.fd, O_RDONLY);
		dup2(g_global_struct.i, 0);
		return (1);
	}
	return (0);
}
