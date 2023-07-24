/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:57:49 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:44:50 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
