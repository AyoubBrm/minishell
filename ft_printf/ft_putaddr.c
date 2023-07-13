/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:39:00 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 03:58:19 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putaddr(unsigned long n, int *lol)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n < 16)
	{
		ft_putchar(hex[n], lol);
	}
	else
	{
		ft_putaddr(n / 16, lol);
		ft_putaddr(n % 16, lol);
	}
}
