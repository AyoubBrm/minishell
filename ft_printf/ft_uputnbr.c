/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:39:20 by shmimi            #+#    #+#             */
/*   Updated: 2022/11/04 03:39:21 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_uputnbr(unsigned int n, int *lol)
{
	if (n >= 0 && n < 10)
		ft_putchar(n + 48, lol);
	else if (n >= 10)
	{
		ft_uputnbr(n / 10, lol);
		ft_uputnbr(n % 10, lol);
	}
	return ;
}
