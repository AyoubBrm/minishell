/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:23:52 by abouram           #+#    #+#             */
/*   Updated: 2023/05/10 18:49:36 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstnew(int x, int y)
// {
// 	t_list	*head;

// 	head = (t_list *)malloc(sizeof(t_list));
// 	if (!head)
// 		return (NULL);
// 	head->x = x;
// 	head->y = y;
// 	head->next = NULL;
// 	return (head);
// }

t_list *ft_lstnew(void *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->value = content;
    new_node->next = NULL;
    return new_node;
}
#include <stdio.h>

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (lst == NULL || del == NULL)
        return;

    del(lst);
    free(lst);
}

void freenode(t_list **lst, t_list *node)
{
    t_list *prev;
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