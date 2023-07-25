/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:26:15 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/23 19:32:11 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_unset(char **to_unset, t_list **my_env)
{
	t_list	*current;
	t_list	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	current = *my_env;
	while (to_unset[i])
	{
		unset_helper(my_env, current, tmp, to_unset[i]);
		current = *my_env;
		i++;
	}
}

void	unset_helper(t_list **my_env, t_list *current, t_list *tmp,
		char *to_unset)
{
	while (current)
	{
		if (current->next && current->key && ft_strncmp(current->key, to_unset,
				ft_strlen(to_unset) + 1) == 0)
		{
			tmp = current->next;
			freenode(my_env, current);
			current = tmp;
		}
		else if (!current->next)
		{
			freenode(my_env, current);
			break ;
		}
		current = current->next;
	}
}

void	freenode(t_list **lst, t_list *node)
{
	t_list	*prev;

	if (*lst == node)
		*lst = (*lst)->next;
	else
	{
		prev = *lst;
		while (prev->next != node)
			prev = prev->next;
		prev->next = node->next;
	}
	free(node->key);
	free(node->value);
	free(node->all);
	node->key = NULL;
	node->value = NULL;
	node->all = NULL;
	free(node);
	node = NULL;
}
