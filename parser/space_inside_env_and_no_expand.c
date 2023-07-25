/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_inside_env_and_no_expand.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:23:50 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 12:01:22 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	space_var2(t_myarg *arg)
{
	if (ft_strchr(" \t", arg->temp_expand[arg->index]))
	{
		arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
				arg->index, arg->index);
		if (arg->temp_expand[arg->index - 1] && !ft_strchr(" \t",
				arg->temp_expand[0]))
			arg->temp_str = ft_strjoin_new(arg->temp_str, "\7", 0, 0);
		if (arg->p)
		{
			free(arg->p);
			arg->p = NULL;
		}
		arg->p = ft_strdup(arg->var);
	}
	else if (arg->temp_expand[arg->index])
		arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
				arg->index, arg->index);
}

void	space_var(t_myarg *arg)
{
	arg->temp_str = ft_calloc(2, 1);
	while (arg->temp_expand[arg->index] && ft_strchr(" \t",
			arg->temp_expand[arg->index]))
		arg->index++;
	while (arg->temp_expand[arg->index])
	{
		while (ft_strchr(" \t", arg->temp_expand[arg->index])
			&& ft_strchr(" \t", arg->temp_expand[arg->index + 1]))
			arg->index++;
		space_var2(arg);
		arg->index++;
	}
}

void	space_center(t_myarg *arg, int *i)
{
	if ((((ft_strchr(arg->temp_expand, ' ') || ft_strchr(arg->temp_expand,
						'\t')))))
	{
		space_var(arg);
		free(arg->temp_expand);
		arg->temp_expand = NULL;
		arg->temp_expand = ft_strdup(arg->temp_str);
		free(arg->temp_str);
		arg->temp_str = NULL;
		arg->ex_env = ft_split_origin(arg->temp_expand, ' ');
		arg->str_new = join_2d_arr(arg->str_new, arg->ex_env);
		*i = -1;
		while (arg->str_new[++(*i)])
		{
			if ((arg->str_new[*i][0] == '\7' && arg->str_new[*i][1] == '\6'
					&& arg->str_new[arg->indx][2] == '\0')
				|| (arg->str_new[*i][0] == '\7' && arg->str_new[*i][1] == '\5'
					&& arg->str_new[*i][2] == '\0'))
				arg->str_new[*i] = 0;
		}
		free2d(arg->ex_env);
	}
	else
		arg->str_new = join2d_with_arr(arg->str_new, arg->temp_expand);
}

void	expand_inside_env_or_dont_expand(t_list *my_env, t_myarg *arg, char **s)
{
	int	i;

	i = -1;
	if ((((ft_strchr(arg->temp_expand, '\6') || ft_strchr(arg->temp_expand,
						'\5')) && (ft_strchr(arg->temp_expand, ' ')
					|| ft_strchr(arg->temp_expand, '\t')))))
	{
		arg->indx = -1;
		check_ambig(my_env, arg, s);
		space_center(arg, &i);
		arg->space = 0;
	}
	else
		arg->str_new = join2d_with_arr(arg->str_new, arg->temp_expand);
}
