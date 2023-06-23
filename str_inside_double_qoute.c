/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_inside_double_qoute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:54:57 by abouram           #+#    #+#             */
/*   Updated: 2023/06/23 13:21:24 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_qoute(char **str, char **s, t_myarg *arg, int star)
{
	arg->i = star;
	while (str[arg->x][arg->i] && str[arg->x][arg->i] != '"')
		arg->i++;
	if ((arg->x == 0) || (arg->x > 0 && str[arg->x - 1][0] == '"' && str[arg->x
			- 1][1] == '"' && !ft_strchr2(" \t", str[arg->x][0], 2))
		|| (arg->x > 0 && str[arg->x - 1][0] == '\'' && str[arg->x
			- 1][1] == '\'' && str[arg->x][0] == '"'))
	{
		if (!s[arg->index])
			s[arg->index] = ft_calloc(1, 1);
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
			- 1);
		// this for first arg between ("asdasda")
	}
	else if ((str[arg->x - 1][0] && ft_strchr2(" \t", str[arg->x
				- 1][ft_strlen(str[arg->x - 1]) - 1], 2)))
		// this is for second string inside (space "asd") and before the string space that mean new strig have to allocted
		s[arg->index] = ft_substr(str[arg->x], star, arg->i - 1);
	else if (arg->x > 0 && str[arg->x - 1])
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
			- 1);
}
void	pipe_rid_insde_qoute(char **str, char **s, t_myarg *arg, int star)
{
	if ((arg->x == 0) || (str[arg->x] && str[arg->x - 1] && ft_strchr2(" \t",
				str[arg->x - 1][0], 2)) || (str[arg->x] && str[arg->x - 1]
			&& ft_strchr2(" \t", str[arg->x - 1][ft_strlen(str[arg->x - 1])
				- 1], 2)))
		s[arg->index] = ft_strdup("\1");
	while (str[arg->x][arg->i] && str[arg->x][arg->i] != '"')
		arg->i++;
	s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
		- 1);
}

void	dollar_inside_qoute(char **str, char **s, t_myarg *arg, int star)
{
	while (str[arg->x][arg->i] == '$')
		arg->i++;
	while (str[arg->x][arg->i] && str[arg->x][arg->i] != '"')
		arg->i++;
	if (str[arg->x][arg->i] == '"')
	{
		if (!s[arg->index])
			s[arg->index] = ft_calloc(1, 1);
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
			- 1);
	}
	s[arg->index] = ft_strjoin_new(s[arg->index], "\3", 0, 0);
}

void	str_inside_double_qoute(char **str, char **s, t_myarg *arg)
{
	int star;

	if (str[arg->x][arg->i] == '"' && str[arg->x][arg->i + 1] != '"')
	{
		arg->i++;
		star = arg->i;
		while (str[arg->x][arg->i] && !ft_strchr2("$|><\"", str[arg->x][arg->i],
				5))
			arg->i++;
		if (str[arg->x][arg->i] == '$')
			dollar_inside_qoute(str, s, arg, star);
		else if (ft_strchr2("|><", str[arg->x][arg->i], 3))
			pipe_rid_insde_qoute(str, s, arg, star);
		else
			inside_qoute(str, s, arg, star);
	}
}