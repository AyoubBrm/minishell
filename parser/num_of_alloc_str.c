/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_of_alloc_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:41:06 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:44:19 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	num_alloc_str2(int *x, char *input, int num_alloc)
{
	if (input[*x] == '"')
	{
		if (input[*x] == '"' && input[*x])
			(*x)++;
		while (input[*x] != '"' && input[*x])
			(*x)++;
		if (input[*x] == '"')
			num_alloc++;
	}
	else if (input[*x] == '\'')
	{
		if (input[*x] == '\'' && input[*x])
			(*x)++;
		while (input[*x] != '\'' && input[*x])
			(*x)++;
		if (input[*x] == '\'')
			num_alloc++;
	}
	return (num_alloc);
}

int	num_alloc_str1(int *x, char *input, int num_alloc)
{
	if (input[*x] != '"' && input[*x] != '\'')
	{
		while (ft_strchr2(" \t", input[*x], 2) && input[*x])
			(*x)++;
		while (input[*x] && !ft_strchr2(" \t\"'><|", input[*x], 7))
			(*x)++;
		if (*x > 0 && input[*x - 1] && ft_strchr2(" ><|\t", input[*x], 6))
			num_alloc++;
	}
	if (ft_strchr("|<>", input[*x]))
	{
		while ((input[*x] == '>' && input[*x + 1] == '>') || (input[*x] == '<'
				&& input[*x + 1] == '<') || (input[*x] == '|' && input[*x
					+ 1] == '|'))
			(*x)++;
		num_alloc++;
	}
	return (num_alloc);
}

int	num_alloc_str(char *input)
{
	int	x;
	int	num_alloc;

	x = 0;
	num_alloc = 0;
	while (input[x])
	{
		num_alloc = num_alloc_str1(&x, input, num_alloc);
		num_alloc = num_alloc_str2(&x, input, num_alloc);
		if (input[x])
			x++;
	}
	return (num_alloc);
}
