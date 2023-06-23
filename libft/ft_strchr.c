/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 22:08:19 by abouram           #+#    #+#             */
/*   Updated: 2023/06/22 22:04:48 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			i++;
			return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}

int	ft_strchr2(char *s, char c, int end)
{
	int	i;

	i = 0;
	while (s[i] && i <= end)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr_inc(char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}
