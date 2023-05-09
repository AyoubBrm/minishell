/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/05/09 23:56:33 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>

#include <stdio.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>

void parser_arg(char *input)
{
	size_t x;
	size_t i = 0;
	char **str;
	char **s;
	int z = 0;
	char **split;
	int a = 0;
	int		star = 0;
	str = ft_split(input, '\"');
	x = 0;
	while (input[x])
	{
		if (input[x] != '"')
		{
			while (input[x] == ' ' && input[x])
					x++;
			while (input[x] != ' ' && input[x] != '"'
				&& input[x + 1] != ' ' && input[x + 1] != '"' && input[x])
					x++;
			if ((input[x] != '"' && input[x] != ' ' && input[x + 1] == ' ')
				|| (input[x] != '"' && input[x] != ' ' && input[x + 1] == '\0')
				|| (input[x] != '"' && input[x] != ' ' && input[x + 1] == '"'))
				a++;
			while (input[x] != ' ' && input[x] != '"' && input[x])
				x++;	
		}
		if (input[x] == '"')
		{
			if (input[x] == '"' && input[x])
				x++;
			while (input[x] != '"' && input[x])
				x++;
			if (input[x] == '"' )
			{
				a++;
				x++;
			}	
		}
		x++;
	}
	s = ft_calloc(sizeof(char *) , a + 5);
	a = 0;
	x = 0;
	while (str[x])
	{
		// if (str[x][i] == '"' && str[x][i + 1] == '"' && str[x][i + 2] == '\0')
		// {
		// 	// s[z] = ft_calloc(1, 1);
		// 	// z++;
		// 	return ;
		// }
		// else if (str[0][i] == '"' && str[0][i + 1] == '"' && str[x + 1][0] == ' ')
		// {
		// 	s[z] = ft_calloc(1, 1);
		// 	break ;
		// }
		if (str[x][i] == '"' && str[x][i + 1] != '"')
		{
				i++;
			star = i;
			while(str[x][i] && str[x][i] != '"')
				i++;
			s[z] = ft_substr(str[x], star, i - star);
			if (str[x + 1] && str[x][i] == '"' && str[x + 1][0] == ' ')
			{
				z++;
				i = 0;
			}
		}
		if ((str[x + 1] && str[x][i] == '"' && str[x][i + 1] == '"' && str[x + 1][0] != ' ') || (str[x][i] == '"' && str[x + 1]))
		{
			if (str[x + 1] && str[x][i] == '"' && str[x + 1][0] != ' ')
				i = 0;
			while (str[x][0] == '"' && str[x][1] == '"')
				x++;
			if(!s[z])
				s[z] = ft_calloc(1,1);
				star = i;
			while(str[x][i] != ' ' && str[x][i])
			{
				while(str[x][i] != '"' && str[x][i] != ' ' && str[x][i])
						i++;
				s[z] = ft_strjoin(s[z], str[x], star, i);
				if (str[x][i] && str[x][i] == '"')
				{
					x++;
					i = 0;
				}
				if(str[x][i] && str[x][i] == ' ')
				{
					while(str[x][i] == ' ')
						i++;
					z++;
					break;
				}
			}
		}
			if (str[x][i] && str[x][i] != '"' && str[x][i] != '\'')
			{
				if (str[x][0] == ' ')
						z++;
				while (str[x][i] == ' ' || str[x][i] == '"')
					i++;
					star = i;
				while (str[x][i] && str[x][i] != '"')
					i++;
				s[z] = ft_substr(str[x], star, i - star);
				split = ft_split2(s[z], ' ');
				while (split[a] != '\0')
				{	
					s[z] = ft_substr(split[a], 0, ft_strlen(split[a]));
					if (split[a + 1] != '\0' || str[x][0] == ' ')
						z++;
					a++;
				}
			}
		x++;
		a = 0;
		i = 0;
	}
	printf("******************************\n");	
	i = 0;
	while (str[i])
		printf("------*str----*%s\n", str[i++]);
	printf("******************************\n");	
	i = 0;
	while (s[i])
		printf("----*s----*%s\n", s[i++]);
}

int	main(int ac, char **av)
{
	int		i;
	char	*input;

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
