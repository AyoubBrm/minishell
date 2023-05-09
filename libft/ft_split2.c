/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:48:51 by abouram           #+#    #+#             */
/*   Updated: 2023/05/06 23:09:52 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_found(char *str, char c)
{
	size_t	i;
	size_t	counter;
	size_t	j;

	j = ft_strlen(str) - 1;
	i = 0;
	counter = 0;
	while (str[i] && i <= j)
	{
		if (str[i] && str[i] == c)
			i++;
		else if (str[i] && str[i] != c)
		{
			while (str[i] != c && str[i])
				i++;
			counter++;
		}
	}
	return (counter);
}

static void	ft_par(char **p, char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	star;
	size_t	end;
	size_t	k;

	j = ft_strlen(s) - 1;
	k = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[j] && s[j] == c)
		j--;
	while (s[i] && i <= j)
	{
		while (s[i] && s[i] == c)
			i++;
		star = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		p[k++] = ft_substr(s, star, end - star);
	}
}

char	**ft_split2(char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)ft_calloc((ft_found(s, c) + 1), sizeof(char *));
	if (!p)
		return (NULL);
	ft_par(p, s, c);
	return (p);
}
