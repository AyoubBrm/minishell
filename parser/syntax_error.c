/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:29:48 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_error(t_table *list, t_table *free, char *temp_pipe, char **temp_file)
{
	if ((temp_pipe && !list->cmd && !temp_file[0]) || (list->pip == 1
			&& !list->next->cmd && list->next->redirection->file
			&& !list->next->redirection->file[0])
		|| (temp_pipe && temp_pipe[0] == '|' && temp_pipe[1] == '|'))
	{
		printf("bash: syntax error\n");
		free_list(free);
		return (1);
	}
	return (0);
}

int	file_error(t_table *free, char **temp_file)
{
	int	x;

	x = 0;
	while (temp_file[x])
	{
		if (temp_file[x] && (!ft_strncmp(temp_file[x], ">", 1)
				|| !ft_strncmp(temp_file[x], "<", 1)
				|| !ft_strncmp(temp_file[x], "<<", 2)
				|| !ft_strncmp(temp_file[x], ">>", 2)))
		{
			printf("bash: syntax error\n");
			free_list(free);
			return (1);
		}
		x++;
	}
	return (0);
}

int	redirection_error(t_table *list, t_table *free, char *temp_red)
{
	if (temp_red && temp_red[1] && ((temp_red[0] == '>' && temp_red[1] != '>')
			|| (temp_red[0] == '<' && temp_red[1] != '<')))
	{
		free_list(free);
		printf("bash: syntax error\n");
		return (1);
	}
	else if (temp_red && ft_strncmp(">>", temp_red, 3) && ft_strncmp("<<",
			temp_red, 3) && (ft_strlen(temp_red) - 1) > 1)
	{
		free_list(free);
		printf("bash: syntax error\n");
		return (1);
	}
	else if (temp_red && !list->redirection->file && list->redirection->pipe)
	{
		free_list(free);
		printf("bash: syntax error\n");
		return (1);
	}
	return (0);
}

int	error_file_pip_rid(t_table *list, t_table *free)
{
	int	x;

	if (list->redirection->pipe && list->redirection->file
		&& pipe_error(list, free, list->redirection->pipe,
			list->redirection->file))
		return (0);
	else if (list->redirection->file && file_error(list,
			list->redirection->file))
		return (0);
	x = -1;
	while (list->redirection->type[++x])
	{
		if (list->redirection->file && !list->redirection->file[0])
			list->redirection->file = NULL;
		if (redirection_error(list, free, list->redirection->type[x]))
			return (0);
		else if (list->redirection->type[x] && !list->redirection->file)
		{
			printf("bash: syntax error\n");
			free_list(free);
			return (0);
		}
	}
	return (1);
}

t_table	*error(t_table *list)
{
	t_table	*head;
	t_table	*free;

	free = list;
	head = list;
	while (list)
	{
		if (error_file_pip_rid(list, free) == 0)
		{
			g_global_struct.g_exit_status = 2;
			return (0);
		}
		list = list->next;
	}
	return (head);
}
