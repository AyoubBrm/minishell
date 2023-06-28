/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:35:59 by abouram           #+#    #+#             */
/*   Updated: 2023/06/27 23:18:24 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	*final_addition(char **str_new)
{
	t_table	*new_addition;
	t_table	*head;
	t_table	*head2;

	new_addition = ft_calloc(1, sizeof(t_table));
	head = new_addition;
	head2 = new_addition;
	new_addition->redirection = ft_calloc(1, sizeof(t_redirection));
	new_addition->redirection->how_many = 0;
	new_addition->redirection->heredoc = 0;
	new_addition->redirection->out_redirection = 0;
	new_addition->redirection->in_redirection = 0;
	new_addition->redirection->append_redirection = 0;
	new_addition->redirection->type = ft_calloc(1, sizeof(char *));
	new_addition->redirection->file = ft_calloc(1, sizeof(char *));
	new_addition->pip = 0;
	new_addition->arg = ft_calloc(1, sizeof(char *));
	new_addition = addition_part(str_new, new_addition);
	head = error(head);
	if (head == 0)
		return (NULL);
	new_addition->next = NULL;
	free2d(str_new);
	ambiguous_no_file(head2);
	return (head);
}
