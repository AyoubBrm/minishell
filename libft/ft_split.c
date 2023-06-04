/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:48:51 by abouram           #+#    #+#             */
/*   Updated: 2023/06/03 05:08:44 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_found_2(char *str, int i, size_t	counter)
{
	if (str[i] == ' ')
	{
		while ((str[i] && str[i] == ' '))
			i++;
		counter++;
	}
	else if (str[i] == '\'')
	{
		if ((str[i] && str[i] == '\''))
			i++;
		while (str[i] != '\'' && str[i])
			i++;
		if ((str[i] == '\'') || (str[i - 1] == '\'' && str[i] == '\0'))
			counter++;
	}
	return (counter);
}

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
		if (str[i] == c)
		{
			if ((str[i] && str[i] == c))
				i++;
			while (str[i] != c && str[i])
				i++;
			if (str[i] == c || (str[i - 1] == c && str[i] == '\0'))
				counter++;
		}
		counter = ft_found_2(str, i, counter);
		i++;
	}
	return (counter);
}

void	ft_par2(char ***p, char **s, size_t *i, size_t *k)
{
	size_t	star;

	if ((*s)[(*i)] == '"')
	{
		star = (*i);
		if ((*s)[(*i) + 1] != '\0')
			(*i)++;
		while (((*s)[(*i)] && (*s)[(*i)] != '"'))
			((*i))++;
		if ((*s)[(*i)] != '\0' && (*s)[(*i)] == '"')
			(*p)[(*k)++] = ft_substr(*s, star, (*i - star) + 1);
	}
	if ((*s)[(*i)] == '\'')
	{
		star = (*i);
		if ((*s)[(*i) + 1] != '\0')
			(*i)++;
		while (((*s)[(*i)] && (*s)[(*i)] != '\''))
			(*i)++;
		if ((*s)[(*i)] && (*s)[(*i)] == '\'')
			(*p)[(*k)++] = ft_substr(*s, star, (*i - star) + 1);
	}
}

static void	ft_par(char **p, char *s, size_t *k)
{
	size_t	i;
	size_t	j;
	size_t	star;
	size_t	end;

	j = ft_strlen(s) - 1;
	*k = 0;
	i = 0;
	while (s[i] && i <= j)
	{
		if (s[i] != '"' && s[i] != '\'')
		{
			star = i;
			while ((s[i] && s[i] != '"' && s[i] != '\''))
				i++;
			end = i - 1;
			p[(*k)++] = ft_substr(s, star, (end - star) + 1);
		}
		ft_par2(&p, &s, &i, k);
		i++;
	}
}

char	**ft_split(char *s, char c)
{
	char	**p;
	size_t	k;

	k = 0;
	if (!s)
		return (NULL);
	p = (char **)ft_calloc((ft_found(s, c) + 10), sizeof(char *));
	if (!p)
		return (NULL);
	ft_par(p, s, &k);
	return (p);
}
