/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_no_dirc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:40:14 by abouram           #+#    #+#             */
/*   Updated: 2023/06/22 22:56:42 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_no_file(t_table *head)
{
	int	i;

	head->ambiguous = 0;
	head->no_file_dire = 0;
	while (head)
	{
		i = -1;
		if (head->cmd && head->cmd[0] == '1')
			ft_memmove(head->cmd, &head->cmd[1], ft_strlen(head->cmd));
		else if (head->cmd && head->cmd[0] == '9')
			head->ambiguous = 1;
		else if (head->cmd && head->cmd[0] == '6')
			head->cmd = NULL;
		else if (head->cmd && (head->cmd[0] == '3' || head->cmd[0] == '5'))
			head->cmd[0] = '\0';
		while (head->arg[++i])
		{
			if (head->arg[i] && head->arg[i][0] == '6')
				head->arg[i][0] = '\0';
		}
		i = -1;
		while (head->redirection->file[++i])
		{
			if (head->redirection->file[i][0] == '6')
			{
				head->ambiguous = 1;
				head->redirection->file[i][0] = '\0';
			}
			else if (head->redirection->file[i][0] == '3'
				|| head->redirection->file[i][0] == '5'
				|| !head->redirection->file[i][0])
			{
				head->no_file_dire = 1;
				head->redirection->file[i][0] = '\0';
			}
			else if (head->redirection->file[i][0] == '1')
				ft_memmove(head->redirection->file[i],
					&head->redirection->file[i][1],
					ft_strlen(head->redirection->file[i]));
		}
		i = -1;
		while (head->arg[++i])
		{
			if (head->arg[i][0] == '3' || head->arg[i][0] == '5'
				|| !head->arg[i][0])
			{
				head->no_file_dire = 1;
				head->arg[i][0] = '\0';
			}
		}
		printf("ambig--%d-----no_file-%d\n", head->ambiguous,
			head->no_file_dire);
		head = head->next;
	}
}
