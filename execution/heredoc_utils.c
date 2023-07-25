/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:14:47 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_utils(t_pipes_n_redirection *pipes_n_redirection,
		t_table *current_heredoc)
{
	if (pipes_n_redirection->input && ft_strncmp(pipes_n_redirection->input,
			current_heredoc->redirection->file
			[pipes_n_redirection->pos_redirection_v2],
			ft_strlen(current_heredoc->redirection->file
				[pipes_n_redirection->pos_redirection_v2])
			+ 1) == 0)
	{
		write(pipes_n_redirection->in, pipes_n_redirection->buffer,
			ft_strlen(pipes_n_redirection->buffer));
		free(pipes_n_redirection->input);
		free(pipes_n_redirection->buffer);
		pipes_n_redirection->pos_redirection++;
		pipes_n_redirection->flag = 1;
		close(pipes_n_redirection->in);
		pipes_n_redirection->in = open(
				pipes_n_redirection->filename,
				O_RDONLY,
				0666);
		return (1);
	}
	return (0);
}

int	heredoc_utils2(t_pipes_n_redirection *pipes_n_redirection,
		t_table *current_heredoc, t_myarg *arg, t_list *my_env)
{
	char	**p;

	if (pipes_n_redirection->input && ft_strchr(pipes_n_redirection->input, '$')
		&& arg->ex_here == 0 && current_heredoc->exp_heredoc == 0)
	{
		pipes_n_redirection->input = ft_strjoin(
				pipes_n_redirection->input,
				"\n");
		p = ft_split_origin(pipes_n_redirection->input, '\n');
		p = expand(p, my_env, arg->num_alloc, arg);
		free(pipes_n_redirection->input);
		pipes_n_redirection->input = ft_strdup(p[0]);
		free2d(p);
	}
	return (0);
}

int	heredoc_utils3(t_pipes_n_redirection *pipes_n_redirection)
{
	if (!pipes_n_redirection->input)
	{
		if (pipes_n_redirection->filename)
		{
			write(pipes_n_redirection->in,
				pipes_n_redirection->buffer,
				ft_strlen(pipes_n_redirection->buffer));
			free(pipes_n_redirection->input);
			free(pipes_n_redirection->buffer);
			pipes_n_redirection->pos_redirection++;
			pipes_n_redirection->flag = 1;
			close(pipes_n_redirection->in);
			pipes_n_redirection->in = open(
					pipes_n_redirection->filename,
					O_RDONLY,
					0666);
		}
		return (1);
	}
	return (0);
}

void	heredoc_join_n_write(t_pipes_n_redirection *pipes_n_redirection)
{
	pipes_n_redirection->tmp_buffer = ft_strjoin_no_free(
			pipes_n_redirection->buffer,
			pipes_n_redirection->input);
	free(pipes_n_redirection->buffer);
	pipes_n_redirection->buffer = ft_strjoin_no_free(
			pipes_n_redirection->tmp_buffer,
			"\n");
	free(pipes_n_redirection->tmp_buffer);
	free(pipes_n_redirection->input);
}

void	heredoc_loop(t_pipes_n_redirection *pipes_n_redirection,
		t_table *current_heredoc, t_myarg *arg, t_list *my_env)
{
	while (1)
	{
		signal(SIGINT, sig_here);
		if (g_global_struct.heredoc_signal == 1)
			break ;
		pipes_n_redirection->input = readline("> ");
		if (heredoc_utils(pipes_n_redirection, current_heredoc))
			break ;
		else if (heredoc_utils2(pipes_n_redirection, current_heredoc, arg,
				my_env))
			break ;
		else if (heredoc_utils3(pipes_n_redirection))
			break ;
		heredoc_join_n_write(pipes_n_redirection);
	}
}
