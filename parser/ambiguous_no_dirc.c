/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_no_dirc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:40:14 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 16:56:59 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_rid(t_table *head, t_myarg *arg)
{
	int	i;

	i = -1;
	while (head->redirection->file[++i])
	{
		if (head->redirection->file[i][0] == '\6' && arg->space == 0)
		{
			head->ambiguous = 1;
			head->redirection->file[i][0] = '\0';
			g_global_struct.g_exit_status = 1;
		}
		else if (head->redirection->file[i][0] == '\3'
			|| head->redirection->file[i][0] == '\5'
			|| !head->redirection->file[i][0])
		{
			head->no_file_dire = 1;
			head->redirection->file[i][0] = '\0';
		}
		else if (head->redirection->file[i][0] == '\1')
			ft_memmove(head->redirection->file[i],
				&head->redirection->file[i][1],
				ft_strlen(head->redirection->file[i]));
	}
}

void	check_arg(t_table *head, t_myarg *arg)
{
	int	i;

	i = -1;
	while (head->arg[++i])
	{
		if (head->arg[i] && head->arg[i][0] == '\7' && arg->space == 0)
		{
			head->ambiguous = 1;
			g_global_struct.g_exit_status = 1;
			ft_memmove(head->arg[i], &head->arg[i][1], ft_strlen(head->arg[i]));
		}
		else if (head->arg[i] && head->arg[i][0] == '\6')
			head->arg[i][0] = '\0';
	}
}

void	cmd_arg(t_table *head, t_myarg *arg)
{
	int	i;

	if (head->cmd && head->cmd[0] == '\1')
		ft_memmove(head->cmd, &head->cmd[1], ft_strlen(head->cmd));
	else if (head->cmd && head->cmd[0] == '\7' && arg->space == 0)
	{
		head->ambiguous = 1;
		g_global_struct.g_exit_status = 1;
	}
	else if (head->cmd && head->cmd[0] == '\6')
	{
		free(head->cmd);
		head->cmd = NULL;
	}
	else if (head->cmd && (head->cmd[0] == '\3' || head->cmd[0] == '\5'))
		head->cmd[0] = '\0';
	check_arg(head, arg);
}

void	ambiguous_no_file(t_table *head, t_myarg *arg)
{
	int	i;

	head->ambiguous = 0;
	head->no_file_dire = 0;
	while (head)
	{
		cmd_arg(head, arg);
		file_rid(head, arg);
		i = -1;
		while (head->arg[++i])
		{
			if ((head->arg[i][0] == '\3' || head->arg[i][0] == '\5')
				|| (!head->arg[i][0] && ft_strncmp(head->cmd, "echo", 5) != 0))
			{
				head->no_file_dire = 1;
				head->arg[i][0] = '\0';
			}
		}
		i = -1;
		head = head->next;
	}
}
