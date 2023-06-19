/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_par.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:02:29 by abouram           #+#    #+#             */
/*   Updated: 2023/06/19 18:28:33 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void for_null_cmd_or_arg(char **str, char **s, t_myarg *arg)
{
if (((((str[arg->x][0] == '"' && str[arg->x][1] == '"')
	|| (str[arg->x][0] == '\'' && str[arg->x][1] == '\''))
	&& (arg->x == 0 && str[arg->x + 1])) && ft_strchr(" \t",
	str[arg->x + 1][0])))
		s[arg->index] = ft_calloc(1, 1);
if (((((str[arg->x][0] == '"' && str[arg->x][1] == '"')
	|| (str[arg->x][0] == '\'' && str[arg->x][1] == '\''))
	&& (arg->x > 0 && str[arg->x + 1] && str[arg->x - 1]))
	&& ft_strchr(" \t", str[arg->x + 1][0]) && ft_strchr(" \t",
		str[arg->x - 1][ft_strlen(str[arg->x - 1]) - 1])))
	s[arg->index] = ft_calloc(1, 1);
if (((str[arg->x][0] == '"' && str[arg->x][1] == '"')
	|| ((str[arg->x][0] == '\'' && str[arg->x][1] == '\'')))
	&& arg->x > 0 && !str[arg->x + 1] && str[arg->x - 1]
	&& ft_strchr(" \t", str[arg->x - 1][ft_strlen(str[arg->x - 1])
	- 1]))
	s[arg->index] = ft_calloc(1, 1);
if (((str[0][0] == '"' && str[0][1] == '"') || ((str[0][0] == '\''
	&& str[0][1] == '\''))) && !str[1])
		s[arg->index] = ft_calloc(1, 1);
}

char	**get_token_from_str(char **str, char **s, t_myarg *arg)
{
	while (str[arg->x])
	{
		if (str[arg->x][arg->i] && !ft_strchr2("\'\"", str[arg->x][arg->i], 2))
		{
			while (str[arg->x][arg->i] && ft_strchr(" \t", str[arg->x][arg->i]))
				arg->i++;
			if (arg->i > 0 && arg->x > 0 && ft_strchr2(" \t", str[arg->x][arg->i
					- 1], 2))
				arg->index++;
			str_and_dollar_with_out_quote(str, s, arg);
		}
		for_null_cmd_or_arg(str, s, arg);
		str_inside_double_qoute(str, s, arg);
		str_inside_single_qoute(str, s, arg);
		arg->x++;
		arg->i = 0;
	}
	// if (str)
	// 	free2d(str);
	return (s);
}