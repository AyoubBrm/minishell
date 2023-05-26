/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:05:06 by abouram           #+#    #+#             */
/*   Updated: 2023/05/23 22:24:38 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_new(char *s1, char *s2, int x, int j)
{
	char	*p;
	int		i;
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	tmp = s1;
	i = 0;
	p = (char *)malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1)
	{
		p[i] = *s1++;
		i++;
	}
	while (s2[x] && x <= j)
	{
		p[i] = s2[x++];
		i++;
	}
	p[i] = '\0';
	free(tmp);
	return (p);
}
