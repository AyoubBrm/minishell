/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   account_the_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:08:36 by abouram           #+#    #+#             */
/*   Updated: 2023/05/29 19:10:10 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int account_quote(char *input)
{
	int	x;
	int	quote;

	x = 0;
	quote = 0;
	while(input[x])
	{
		if (input[x] == '"')
		{
			x++;
			quote++;
			while (input[x] && input[x] != '"')
				x++;
			if (input[x] == '"')
				quote++;
		}
		if (input[x] == '\'')
		{
			x++;
			quote++;
			while (input[x] && input[x] != '\'')
				x++;
			if (input[x] == '\'')
				quote++;
		}
		x++;
	}
	return (quote);
}