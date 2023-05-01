/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram <abouram@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:05:31 by abouram           #+#    #+#             */
/*   Updated: 2022/10/22 00:30:58 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*a;
	t_list	*b;

	if (!lst)
		return (NULL);
	a = lst;
	while (a)
	{
		b = a;
		a = a->next;
	}
	return (b);
}
