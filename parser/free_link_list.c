/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_link_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:15:35 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 11:17:36 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_table *head)
{
	t_table	*new_addition;

	while (head)
	{
		free(head->cmd);
		free2d(head->redirection->type);
		free(head->redirection->pipe);
		free2d(head->arg);
		free2d(head->redirection->file);
		free(head->redirection);
		new_addition = head->next;
		free(head);
		head = new_addition;
	}
	free(head);
}
