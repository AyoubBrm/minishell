/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexxx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:39:08 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 04:01:08 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexxx(unsigned int n, int *lol)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n < 16)
		ft_putchar(hex[n], lol);
	else
	{
		ft_putnbr_hexxx(n / 16, lol);
		ft_putnbr_hexxx(n % 16, lol);
	}
}
