/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_without_quotev2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:35:08 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:45:01 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_without_quotev2(char **str, char **s, t_myarg *arg, int star)
{
	if ((str[arg->x][0] == '"' && str[arg->x][1] != '"' ))
	{
		star = 1;
		arg->i = 1;
		while (str[arg->x] && str[arg->x][arg->i] != '"')
			arg->i++;
		s[arg->index] = ft_strjoin_new(s[arg->index],
				str[arg->x], star, arg->i - 1);
	}
	else if ((str[arg->x][0] == '\'' && str[arg->x][1] != '\'' ))
	{
		star = 1;
		arg->i = 1;
		while (str[arg->x] && str[arg->x][arg->i] != '\'')
			arg->i++;
		s[arg->index] = ft_strjoin_new(s[arg->index],
				str[arg->x], star, arg->i - 1);
	}
}
