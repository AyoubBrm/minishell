/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:07 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 16:50:21 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addition_cmd(char **str_new, int *i, t_table *new_addition)
{
	if (str_new[*i] && !new_addition->cmd && str_new[*i][0] != '|')
		new_addition->cmd = ft_strdup(str_new[(*i)++]);
	if (str_new[*i] && str_new[*i][0] && str_new[*i][0] != '\6'
		&& !new_addition->cmd && str_new[*i][0] != '|')
		new_addition->cmd = ft_strdup(str_new[(*i)++]);
	if (str_new[*i] && str_new[*i][0] && str_new[*i][0] == '\6')
		(*i)++;
}

t_table	*output_rid_and_cmd(char **str_new, int *i, t_table *new_addition)
{
	new_addition->redirection->type = join2d_with_arr
		(new_addition->redirection->type, str_new[(*i)++]);
	new_addition->redirection->how_many++;
	new_addition->redirection->out_redirection++;
	if (str_new[*i] && str_new[*i][0] != '|')
	{
		if (str_new[*i][0] == '\7')
			ft_memmove(str_new[*i], &str_new[*i][1], ft_strlen(str_new[*i]));
		new_addition->redirection->file = join2d_with_arr
			(new_addition->redirection->file, str_new[(*i)++]);
	}
	else
	{
		free2d(new_addition->redirection->file);
		new_addition->redirection->file = NULL;
	}
	return (new_addition);
}
