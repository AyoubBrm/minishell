/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_origin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:15:26 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/20 00:20:55 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char delimeter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == delimeter && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != delimeter && s[i])
			i++;
		count++;
	}
	return (count);
}

static int	count_chars(char *s, char c, int *st)
{
	int	i;

	i = 0;
	while (s[*st] != c && s[*st])
	{
		i++;
		(*st)++;
	}
	return (i);
}

static void	assign(char *s, char delimeter, char **tab, int word_counts)
{
	int	i;
	int	fixed;
	int	second_dimension;

	i = 0;
	fixed = 0;
	while (i < word_counts)
	{
		second_dimension = 0;
		while (s[fixed] == delimeter && s[fixed])
			fixed++;
		while (s[fixed] != delimeter && s[fixed])
			tab[i][second_dimension++] = s[fixed++];
		tab[i][second_dimension] = 0;
		i++;
	}
	tab[i] = 0;
}

char	**ft_split_origin(char *s, char c)
{
	int		i;
	char	**tab;
	int		cw;
	int		st;

	i = 0;
	st = 0;
	if (s)
	{
		cw = count_words((char *)s, c);
		tab = (char **)malloc(sizeof(char *) * (cw + 1));
		if (!tab)
			return (0);
		while (i < cw)
		{
			while (s[st] == c && s[st])
				st++;
			tab[i++] = (char *)malloc(count_chars((char *)s, c, &st) + 1);
			if (!s[i - 1])
				return (0);
		}
		assign((char *)s, c, tab, cw);
		return (tab);
	}
	return (0);
}

// int main()
// {
// 	printf("%d", count_words("Hello World /n "), );
// }