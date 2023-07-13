/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:39:12 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 03:39:13 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *lol)
{
	if (n >= 0 && n < 10)
		ft_putchar(n + 48, lol);
	else if (n >= 10)
	{
		ft_putnbr(n / 10, lol);
		ft_putnbr(n % 10, lol);
	}
	if (n == -2147483648)
	{
		ft_putchar('-', lol);
		ft_putchar('2', lol);
		ft_putnbr(147483648, lol);
	}
	else if (n < 0)
	{
		ft_putchar('-', lol);
		n *= -1;
		ft_putnbr(n, lol);
	}
	return ;
}
