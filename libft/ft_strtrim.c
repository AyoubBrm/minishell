/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:29:42 by abouram           #+#    #+#             */
/*   Updated: 2022/12/20 01:49:46 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*p;
	int		f;
	int		b;

	if (!s1)
		return (NULL);
	if (!s1 && !set)
		return (NULL);
	f = 0;
	b = ft_strlen(s1) - 1;
	while (s1[f] && ft_strchr(set, s1[f]))
		f++;
	while (b >= 0 && ft_strrchr(set, s1[b]))
		b--;
	p = ft_substr(s1, f, (b - f) + 1);
	return (p);
}
