/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_inside_env_and_no_expand.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:23:50 by abouram           #+#    #+#             */
/*   Updated: 2023/06/26 19:07:52 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_var(t_myarg *arg)
{
	if (!arg->temp_str)
		arg->temp_str = ft_calloc(1, 1);
	while (arg->temp_expand[arg->index] && ft_strchr(" \t",
			arg->temp_expand[arg->index]))
		arg->index++;
	while (arg->temp_expand[arg->index])
	{
		while (ft_strchr(" \t", arg->temp_expand[arg->index])
			&& ft_strchr(" \t", arg->temp_expand[arg->index + 1]))
			arg->index++;
		if (ft_strchr(" \t", arg->temp_expand[arg->index]))
		{
			arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
					arg->index, arg->index);
			if (arg->temp_expand[arg->index - 1] && !ft_strchr(" \t",
					arg->temp_expand[0]))
				arg->temp_str = ft_strjoin_new(arg->temp_str, "\7", 0, 0);
		}
		else
			arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
					arg->index, arg->index);
		arg->index++;
	}
}

void	expand_inside_env_or_dont_expand(t_myarg *arg)
{
	if (((ft_strchr(arg->temp_expand, '\6') || ft_strchr(arg->temp_expand,
					'\5')) && (ft_strchr(arg->temp_expand, ' ')
				|| ft_strchr(arg->temp_expand, '\t'))))
	{
		if ((ft_strchr(arg->temp_expand, ' ') || ft_strchr(arg->temp_expand,
					'\t')))
		{
			space_var(arg);
			arg->temp_expand = ft_strdup(arg->temp_str);
			free(arg->temp_str);
			arg->temp_str = NULL;
		}
		arg->ex_env = ft_split_origin(arg->temp_expand, ' ');
		arg->str_new = join_2d_arr(arg->str_new, arg->ex_env);
		free2d(arg->ex_env);
	}
	else
		arg->str_new = join2d_with_arr(arg->str_new, arg->temp_expand);
}
