/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   account_the_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:08:36 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:43:13 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	account_quote(char *input, t_myarg *arg)
{
	arg->x = 0;
	arg->quote = 0;
	while (input[arg->x])
	{
		if (input[arg->x] == '"')
		{
			arg->x++;
			arg->quote++;
			while (input[arg->x] && input[arg->x] != '"')
				arg->x++;
			if (input[arg->x] == '"')
				arg->quote++;
		}
		if (input[arg->x] == '\'')
		{
			arg->x++;
			arg->quote++;
			while (input[arg->x] && input[arg->x] != '\'')
				arg->x++;
			if (input[arg->x] == '\'')
				arg->quote++;
		}
		if (input[arg->x])
			arg->x++;
	}
}
