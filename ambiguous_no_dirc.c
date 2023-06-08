/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_no_dirc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:40:14 by abouram           #+#    #+#             */
/*   Updated: 2023/06/09 00:57:35 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ambiguous_no_file(t_table *head)
{
	int	i;

	i = -1;
	head->ambiguous = 0;
	head->no_file_dire = 0;
	while (head)
	{
		while (head->redirection->file[++i])
		{
			if (head->redirection->file[i][0] == '3'
				|| head->redirection->file[i][0] == '5')
			{
				head->no_file_dire = 1;
				head->redirection->file[i][0] = '\0';
			}
			if (head->redirection->file[i][0] == '6')
				head->ambiguous = 1;			
		}
		i = -1;
		if (head->redirection->file == NULL)
		{
			if (head->cmd && head->cmd[0] == '9')
				ft_memmove(head->cmd, &head->cmd[1], ft_strlen(head->cmd));
		}
		i = 0;
			printf("ambig--%d-----no_file-%d\n",head->ambiguous, head->no_file_dire);
		i = 0;
		head = head->next;
	}
}