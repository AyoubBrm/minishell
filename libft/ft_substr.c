/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:51:20 by abouram           #+#    #+#             */
/*   Updated: 2023/06/03 05:32:17 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	a;

	if (!s)
		return (NULL);
	a = ft_strlen(s);
	i = 0;
	if (start > a)
		return (ft_strdup(""));
	if (len > a)
		len = a;
	p = (char *)ft_calloc((len + 1), sizeof(char));
	if (!p)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	return (p);
}
