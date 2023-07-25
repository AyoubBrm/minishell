/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_without_quote_and_dollar.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:00:18 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 16:53:41 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

void	token2(char **str, char **s, t_myarg *arg, int star)
{
	if (str[arg->x][arg->i] && ft_strchr2("|", str[arg->x][arg->i], 1))
		pars_pipe_and_rid(str, s, arg);
	else if (str[arg->x][arg->i] && ft_strchr2("<>", str[arg->x][arg->i], 3))
	{
		if ((arg->i > 0 && !ft_strchr2(&str[arg->x][0], ' ', arg->i)
			&& !ft_strchr2(&str[arg->x][0], '\t', arg->i)) || (arg->x > 0
			&& arg->i == 0))
			arg->index++;
		else if (arg->i > 0 && str[arg->x][arg->i - 1] && !ft_strchr2(" \t",
				str[arg->x][arg->i - 1], 2))
			arg->index++;
		star = arg->i;
		if (!s[arg->index])
			s[arg->index] = ft_calloc(1, 1);
		while (str[arg->x][arg->i] && ft_strchr2("<>", str[arg->x][arg->i], 3))
			arg->i++;
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
				- 1);
		token_v2(str, s, arg);
	}
}

void	token_without_quote(char **str, char **s, t_myarg *arg, int star)
{
	if ((str[arg->x + 1] && str[arg->x][arg->i] == '$' && str[arg->x][arg->i
		+ 1] == '\0' && str[arg->x + 1][0] == '"') || (str[arg->x + 1]
		&& str[arg->x][arg->i] == '$' && str[arg->x][arg->i + 1] == '\0'
		&& str[arg->x + 1][0] == '\''))
	{
		if (arg->i > 0 && str[arg->x][arg->i] == '$'
				&& ft_strchr("\t ", str[arg->x][arg->i - 1]))
			arg->x++;
		if (!s[arg->index])
			s[arg->index] = ft_calloc(1, 1);
		if (str[arg->x][0] != '"' && str[arg->x][1] != '"'
			&& str[arg->x][0] != '\'' && str[arg->x][1] != '\'')
			s[arg->index] = ft_strjoin_new(s[arg->index],
					str[arg->x], star, arg->i - 1);
		token_without_quotev2(str, s, arg, star);
		if (str[arg->x + 1])
		{
			arg->x++;
			arg->i = 0;
		}
	}
	else
		token2(str, s, arg, star);
}

void	for_5_6(char **str, char **s, t_myarg *arg)
{
	if (str[arg->x + 1] && !ft_strchr2(" \t", str[arg->x][arg->i], 2)
		&& str[arg->x + 1][0] == '"' && str[arg->x + 1][1] == '"')
		s[arg->index] = ft_strjoin_new(s[arg->index], "\5", 0, 1);
	else if (arg->x > 0 && !ft_strchr2(" \t", str[arg->x][arg->i], 2)
		&& str[arg->x - 1][0] == '"' && str[arg->x - 1][1] == '"')
		s[arg->index] = ft_strjoin_new(s[arg->index], "\5", 0, 1);
	else if (str[arg->x + 1] && !ft_strchr2(" \t", str[arg->x][arg->i], 2)
		&& str[arg->x + 1][0] == '\'' && str[arg->x + 1][1] == '\'')
		s[arg->index] = ft_strjoin_new(s[arg->index], "\5", 0, 1);
	else if (arg->x > 0 && !ft_strchr2(" \t", str[arg->x][arg->i], 2)
		&& str[arg->x - 1][0] == '\'' && str[arg->x - 1][1] == '\'')
		s[arg->index] = ft_strjoin_new(s[arg->index], "\5", 0, 1);
	else
		s[arg->index] = ft_strjoin_new(s[arg->index], "\6", 0, 0);
}

void	token(char **str, char **s, t_myarg *arg, int star)
{
	if (!s[arg->index])
		s[arg->index] = ft_calloc(1, 1);
	while (str[arg->x][arg->i] && !ft_strchr2("\'\" \t$><|",
			str[arg->x][arg->i], 8))
		arg->i++;
	if ((str[arg->x] && str[arg->x][arg->i] == '$' && str[arg->x][arg->i + 1])
		|| (str[arg->x] && str[arg->x][arg->i] == '$' && str[arg->x][arg->i
			+ 1] == '\0' && !str[arg->x + 1]))
	{
		arg->i++;
		while ((str[arg->x][arg->i] && !ft_strchr2("\t $><|",
				str[arg->x][arg->i], 6)))
			arg->i++;
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
				- 1);
		for_5_6(str, s, arg);
	}
	else if (str[arg->x][arg->i] != '$')
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], star, arg->i
				- 1);
	if (ft_strchr2(" \t", str[arg->x][arg->i], 2))
		arg->index++;
	while (ft_strchr2(" \t", str[arg->x][arg->i], 2))
		arg->i++;
}

void	str_and_dollar_with_out_quote(char **str, char **s, t_myarg *arg)
{
	int	star;

	star = 0;
	if (str[arg->x][arg->i] && !ft_strchr2("\'\"", str[arg->x][arg->i], 2))
	{
		star = arg->i;
		while (str[arg->x][arg->i] && !ft_strchr2("\'\"", str[arg->x][arg->i],
				2))
		{
			token(str, s, arg, star);
			token_without_quote(str, s, arg, star);
			star = arg->i;
		}
	}
}
