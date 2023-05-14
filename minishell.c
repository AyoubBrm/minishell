/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/05/14 22:42:10 by abouram          ###   ########.fr       */
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

void parser_arg(char *input, char **env)
{
	size_t x;
	size_t i = 0;
	char **str;
	char **s;
	int z = 0;
	int a = 0;
	int quote = 0;
	int		star = 0;
	(void)env;
	// while (*env)
	// 	printf("%s\n",*env++);
	str = ft_split(input, '\"');
	x = 0;
	while (str[x])
	{
		if (str[x][i] && str[x][i] == '"') // this for this "" '' if is " % 2 == 1 exit whit syntax eroor ;
		{
			i++;
			quote++;
			while (str[x][i] && str[x][i] != '"')
				i++;
				if (str[x][i] == '"')
					quote++;
		}
		else if (str[x][i] && str[x][i] == '\'')
		{
			i++;
			quote++;
			while (str[x][i] && str[x][i] != '\'')
				i++;
			if (str[x][i] && str[x][i] == '\'')
				quote++;
		}
		if ((quote > 0 && !str[x + 1]) || str[x][i] == '|')
		{
			if (quote % 2 == 1)
				exit (1);
			else
				quote = 0;
		}
		i = 0;
		x++;
	}
	x = 0;
	i = 0;
	while (input[x])
	{
		if (input[x] != '"' && input[x] != '\'') // this for allocte the string **str
		{
			while (input[x] == ' ' && input[x])
					x++;
			while (input[x] != ' ' && input[x] != '"' && input[x] != '\''
				&& input[x + 1] != ' ' && input[x + 1] != '"' && input[x + 1] != '\'' && input[x])
					x++;
			if ((input[x] != '"' && input[x] != ' ' && input[x] != '\'' && input[x + 1] == ' ')
				|| (input[x] != '"' && input[x] != '\'' && input[x] != ' ' && input[x + 1] == '\0')
				|| (input[x] != '"' && input[x] != '\'' && input[x] != ' ' && input[x + 1] == '"'))
				a++;
			while (input[x] != ' ' && input[x] != '"' && input[x] != '\'' && input[x])
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
		if (input[x] == '\'')
		{
			if (input[x] == '\'' && input[x])
				x++;
			while (input[x] != '\'' && input[x])
				x++;
			if (input[x] == '\'' )
			{
				a++;
				x++;
			}	
		}
		x++;
	}
	s = ft_calloc(sizeof(char *) , a + 2);
	a = 0;
	x = 0;
	while (str[x])
	{
		if (str[x][i] && str[x][i] != '"' && str[x][i] != '\'')
		{
			if (str[x][0] == ' ') 
				z++;
			while (str[x][i] == ' ')
				i++;
			if (str[x][i] && str[x][i] != '"')
			{
				star = i;
				while (str[x][i] && str[x][i] != '"')
				{	
					if ((str[x] && str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '"')
						|| (str[x] && str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '\''))
					{
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						x++;
						i = 0;
						star = 0;
						while(str[x][i] && str[x][i] != '\'' && str[x][i] != '"' && str[x][i] != ' ')
							i++;
						s[z] = ft_strjoin(s[z], str[x], star, i - 1);
					}
					else
					{
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						while(str[x][i] && str[x][i] != '"' && str[x][i] != ' ' && str[x][i] != '$')
							i++;
						if ((str[x][i] == '$' && str[x][i + 1]) || (str[x][i] == '$' && str[x][i + 1] == '\0' && !str[x + 1]))
							i++;
						s[z] = ft_strjoin(s[z], str[x], star, i - 1);
						if (str[x][i] == ' ' )
							z++;
						while (str[x][i] == ' ')
							i++;
						star = i;
					}
				}
			}
		}
		if ((str[x][i] && str[x + 1] && str[x - 1] && x > 0 && str[x][0] == '"' // when string -1 and string +1 : is exist this code for this arg (ss "" ss "" ss) before string space and after it and inside string '\0' this for "" qoute index most be > 0
			&& str[x][1] == '"' && str[x + 1][0] == ' ' && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
			|| (str[x][i] && str[x + 1] && str[x - 1] && x > 0 && str[x][0] == '\''// when string -1 and string +1 : is exist this code for this arg (ss '' ss '' ss) before string space and after it and inside string '\0' this for '' qoute index most be > 0
			&& str[x][1] == '\'' && str[x + 1][0] == ' ' && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ') 
			|| (x > 0 && str[x - 1] && str[x] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ' && str[x][0] == '"' && str[x][1] == '"') // when string -1 and string +1 : is exist this code for this arg (ss '' ss '' ss) before string space and after it and inside string '\0' this for '' qoute index most be > 0
			|| (x > 0 && str[x - 1] && str[x] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ' && str[x][0] == '\'' && str[x][1] == '\''))
		{
			if (!s[z])
				s[z] = ft_calloc(1, 1);
		}
		if (str[x][i] == '"' && str[x][i + 1] != '"')
		{
				i++;
			star = i;
			while (str[x][i] && str[x][i] != '"' && str[x][i] != '>' && str[x][i] != '|' && str[x][i] != '<')
				i++;
			if (str[x][i] == '>' || str[x][i] == '|' || str[x][i] == '<')
			{
				if ((x == 0 ) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
					|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
					|| (str[x] && str[x + 1] && str[x + 1][0] == ' '))
						s[z] = ft_strdup("'");
				while (str[x][i] && str[x][i] != '"')    //this for "|" pipe inside quote
					i++;
				s[z] = ft_strjoin(s[z], str[x], star, i - 1);
			}
			else
			{
				i = star;
				while(str[x][i] && str[x][i] != '"')
					i++;
				if ((x == 0) || (x > 0 && str[x - 1] && str[x - 1][0] == '"' && str[x - 1][1] == '"' && str[x][0] != ' ')
				|| (x > 0 && str[x - 1] && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && str[x][0] == '"'))
					s[z] = ft_substr(str[x], star, i - star); // this for first arg between ("asdasda")
				else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')) // this is for second string inside (space "asd") and before the string space that mean new strig have to allocted
					s[z] = ft_substr(str[x], star, i - star);
				else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
					s[z] = ft_strjoin(s[z], str[x], star, i - 1);
			}
		}
		if (str[x][i] == '\'' && str[x][i + 1] != '\'')
		{
				i++;
			star = i;
		while (str[x][i] && str[x][i] != '\'' && str[x][i] != '>' && str[x][i] != '|' && str[x][i] != '<')
				i++;
			if (str[x][i] == '>' || str[x][i] == '|' || str[x][i] == '<')
			{
				if ((x == 0) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
					|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
						s[z] = ft_strdup("'");
				while (str[x][i] && str[x][i] != '\'')    //this for '|' pipe inside quote
					i++;
				s[z] = ft_strjoin(s[z], str[x], star, i - 1);
			}
			else
			{
				i = star;
				while(str[x][i] && str[x][i] != '\'')
					i++;
				if ((x == 0) || (x > 0 && str[x - 1] && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && str[x][0] != ' ')
					|| (x > 0 && str[x - 1] && str[x - 1][0] == '"' && str[x - 1][1] == '"' && str[x][0] == '\''))
					s[z] = ft_substr(str[x], star, i - star);
				else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
					s[z] = ft_substr(str[x], star, i - star);
				else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
					s[z] = ft_strjoin(s[z], str[x], star, i - 1);
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

int	main(int ac, char **av, char **env)
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
		parser_arg(input, env);
		// printf("%s\n", input);
	}
	return (0);
}
