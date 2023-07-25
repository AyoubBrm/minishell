/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:57:49 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 16:39:17 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_pipe_and_rid(char **str, char **s, t_myarg *arg)
{
	if (arg->x > 0 && !ft_strchr(" \t><", str[arg->x - 1][ft_strlen(str[arg->x]
				- 1) - 1]) && arg->i > 0 && !ft_strchr(" \t><",
			str[arg->x][arg->i - 1]))
		arg->index++;
	else if (arg->x == 0 && arg->i > 0 && !ft_strchr(" \t><", str[arg->x][arg->i
			- 1]))
		arg->index++;
	if (!s[arg->index])
		s[arg->index] = ft_calloc(1, 1);
	while (str[arg->x][arg->i] == '|')
	{
		s[arg->index] = ft_strjoin_new(s[arg->index], str[arg->x], arg->i,
				arg->i);
		arg->i++;
	}
	if (str[arg->x][arg->i] && !ft_strchr(" \t><", str[arg->x][arg->i]))
		arg->index++;
}

void	token_v2(char **str, char **s, t_myarg *arg)
{
	if (!ft_strchr("\t ", str[arg->x][arg->i]) && str[arg->x][arg->i])
		arg->index++;
	else if (!ft_strchr2(&str[arg->x][arg->i], ' ', ft_strlen(str[arg->x])
		- arg->i) && (!ft_strchr2(&str[arg->x][arg->i], '\t',
				ft_strlen(str[arg->x]) - arg->i)) && str[arg->x + 1])
		arg->index++;
	if (!s[arg->index])
		s[arg->index] = ft_calloc(1, 1);
}
