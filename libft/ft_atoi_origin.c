/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_origin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:14:29 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/17 18:51:33 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_test(long *result, int i, int *sign, char *nb)
{
	if (*result == 214748364 && (nb[i] - '0') == 8 && *sign == -1)
	{
		*result = 2147483648;
		return (1);
	}
	else if ((*result > 2147483647 / 10) || (*result == 2147483647 / 10
			&& (nb[i] - '0') > 7))
	{
		return (255);
	}
	*result *= 10;
	if ((nb[i] >= '0' && nb[i] <= '9'))
		*result += nb[i] - '0';
	return (0);
}

static void	check(char *nb, int i, long *result, int *sign)
{
	while ((nb[i] >= '0' && nb[i] <= '9') || (nb[i] == '-' || nb[i] == '+'))
	{
		if (nb[i] == '-')
		{
			if (nb[i + 1] == '-' || nb[i + 1] == '+')
				break ;
			*sign = -1;
		}
		else if (nb[i] == '+')
		{
			if (nb[i + 1] == '-' || nb[i + 1] == '+')
				break ;
			*sign = 1;
		}
		check_test(result, i, sign, nb);
		i++;
	}
}

long	ft_atoi_origin(char *str)
{
	int		sign;
	int		i;
	long	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	check(str, i, &result, &sign);
	result = result * sign;
	return (result);
}
