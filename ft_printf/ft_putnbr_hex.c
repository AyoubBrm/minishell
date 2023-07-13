/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:39:06 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 03:58:30 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex(unsigned int n, int *lol)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n < 16)
		ft_putchar(hex[n], lol);
	else
	{
		ft_putnbr_hex(n / 16, lol);
		ft_putnbr_hex(n % 16, lol);
	}
}
