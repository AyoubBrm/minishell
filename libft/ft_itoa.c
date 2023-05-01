/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram <abouram@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:11:10 by abouram           #+#    #+#             */
/*   Updated: 2022/10/21 17:28:01 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reverce(char *re)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = ft_strlen(re) - 1;
	while (re[i] && i < j)
	{
		if (re[i] == '-')
			i++;
		temp = re[i];
		re[i] = re[j];
		re[j] = temp;
		i++;
		j--;
	}
	return (re);
}

static int	count(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		if (n != 0)
			n = n / 10;
		i++;
	}
	return (i);
}

static void	countp(char *p, int n)
{
	int		i;
	long	k;

	i = 0;
	k = n;
	while (k != 0)
	{
		if (k < 0)
		{
			p[i++] = '-';
			k = k * -1;
		}
		if (k > 0)
		{
			p[i] = k % 10 + '0';
			k /= 10;
			i++;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	i = count(n);
	p = (char *)ft_calloc((i + 2), sizeof(char));
	if (!p)
		return (NULL);
	countp(p, n);
	ft_reverce(p);
	return (p);
}
