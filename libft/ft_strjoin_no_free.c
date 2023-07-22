/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:05:06 by abouram           #+#    #+#             */
/*   Updated: 2023/07/22 17:08:34 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	char	*p;
	int		i;
	char	*tmp;

	tmp = s1;
	if (!s1 && !s2)
		return (NULL);
	i = 0;
	p = (char *)malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1)
	{
		p[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		p[i] = *s2++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
