/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:38:57 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/12 16:59:43 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
void	ft_putchar(char c, int *lol);
void	ft_putstr(char *s, int *count);
void	ft_putnbr(int n, int *lol);
void	ft_uputnbr(unsigned int n, int *lol);
void	ft_putnbr_hex(unsigned int n, int *lol);
void	ft_putnbr_hexxx(unsigned int n, int *lol);
void	ft_putaddr(unsigned long n, int *lol);

#endif