/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/05/01 16:01:08 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>

void parser_arg(char *input)
{

	size_t x = 0;
	char **str;
	str = ft_split(input, '"');
	x = 0;
	while (str[x])
	{
		printf("%s\n", str[x++]);
	}
}

int main(int ac, char **av)
{
	int i;
	char *input;

	(void)av;
	i = 0;
	if (ac != 1)
		return (1);
	while (1)
	{
		input = readline("minishell ~$ ");
		add_history(input);
		parser_arg(input);
		// printf("%s\n", input);
	}
	return (0);
}
