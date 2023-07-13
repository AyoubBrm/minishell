/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:38:42 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 04:05:49 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	if_checks(const char s, va_list args, int *lol)
{
	if (s == 'c')
		ft_putchar(va_arg(args, int), lol);
	else if (s == 's')
		ft_putstr((va_arg(args, char *)), lol);
	else if (s == 'd' || s == 'i')
		ft_putnbr(va_arg(args, int), lol);
	else if (s == 'u')
		ft_uputnbr(va_arg(args, unsigned int), lol);
	else if (s == 'x')
		ft_putnbr_hex(va_arg(args, unsigned int), lol);
	else if (s == 'X')
		ft_putnbr_hexxx(va_arg(args, unsigned int), lol);
	else if (s == 'p')
	{
		ft_putstr("0x", lol);
		ft_putaddr(va_arg(args, unsigned long), lol);
	}
	else if (s == '%')
		ft_putchar('%', lol);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		counter;
	int		lol;

	va_start(args, s);
	lol = 0;
	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if_checks(s[i++], args, &lol);
			counter++;
			counter = lol;
		}
		else
		{
			ft_putchar(s[i++], &lol);
			counter++;
		}
	}
	return (counter);
}
