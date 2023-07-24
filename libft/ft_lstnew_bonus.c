/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:23:52 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:15:22 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst);
	free(lst);
}

void	freenode(t_list **lst, t_list *node)
{
	t_list	*prev;

	if (*lst == node)
		*lst = node->next;
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
	free(node);
}
