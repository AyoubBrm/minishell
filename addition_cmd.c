/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:15:07 by abouram           #+#    #+#             */
/*   Updated: 2023/06/27 23:32:50 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_table	*output_rid_and_cmd(char **str_new, int *i, t_table *new_addition)
{
	new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type,
		str_new[(*i)++]);
	new_addition->redirection->how_many++;
	new_addition->redirection->out_redirection++;
	if (str_new[*i] && str_new[*i][0] != '|')
	{
		if (str_new[*i][0] == '\7')
			ft_memmove(str_new[*i], &str_new[*i][1],
				ft_strlen(str_new[*i]));
		new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file,
			str_new[(*i)++]);
    }
	return (new_addition);
}
