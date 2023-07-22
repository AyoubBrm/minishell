/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_inside_env_and_no_expand.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:23:50 by abouram           #+#    #+#             */
/*   Updated: 2023/07/22 17:29:18 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strchr(" \t", arg->temp_expand[arg->index]))
		{
			arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
					arg->index, arg->index);
			if (arg->temp_expand[arg->index - 1] && !ft_strchr(" \t",
					arg->temp_expand[0]))
				arg->temp_str = ft_strjoin_new(arg->temp_str, "\7", 0, 0);
			arg->p = ft_strdup(arg->var);
		}
		else if (arg->temp_expand[arg->index])
		{
			arg->temp_str = ft_strjoin_new(arg->temp_str, arg->temp_expand,
					arg->index, arg->index);
		}
		arg->index++;
	}
}

void expand_inside_env_or_dont_expand(t_list *my_env,t_myarg *arg, char **s)
{
	int i = -1;

	if ((((ft_strchr(arg->temp_expand, '\6') 
		|| ft_strchr(arg->temp_expand, '\5')) && (ft_strchr(arg->temp_expand, ' ')
		|| ft_strchr(arg->temp_expand, '\t')))))
	{
		while (s[arg->x][++i])
		{
			if (i > 0 && s[arg->x][i] == '$' && s[arg->x][i - 1] == '\2')
					arg->space = 1;
			else if (s[arg->x][i] == '$')
			{
				while (s[arg->x][i])
				{
					if (s[arg->x][i] == '\2')
						arg->space = 2;
					i++;
				}
				if (!s[arg->x][i])
					break;
			}
		}
		if ((arg->x > 0 && (!ft_strncmp(s[arg->x - 1], ">", 1) || !ft_strncmp(s[arg->x - 1], "<", 2)) && (arg->space == 1 || arg->space == 2)))
		{
			arg->tmp = ft_calloc(1,1);
			arg->tmp = find_in_env_and_alloced(my_env, arg->var, arg->tmp, 0);
			if (arg->tmp && arg->tmp[0] == ' ' && arg->space == 1)
			{
				arg->ambg = 2;
				arg->p = ft_strdup(arg->var);
				global_struct.g_exit_status = 1;
			}
			if (arg->tmp && arg->tmp[ft_strlen(arg->tmp) - 1] == ' ' && arg->space == 2)
			{
				arg->ambg = 2;
				arg->p = ft_strdup(arg->var);
				free(arg->var);
				global_struct.g_exit_status = 1;
			}
			else
			{
				i = 0;
				while (arg->tmp[i])
				{
					if (arg->tmp[i] && arg->tmp[i] != ' ')
					{
						while(arg->tmp[i])
						{
							if (arg->tmp[i] == ' ')
							{
								while (arg->tmp[i] == ' ')
									i++;
								if (arg->tmp[i] && arg->tmp[i] != ' ')
								{
									arg->ambg = 2;
									arg->p = ft_strdup(arg->var);
								}
							}
							i++;
						}
					}
					if (arg->tmp[i])
						i++;
				}
			}
			free(arg->tmp);
		}
		if ((((ft_strchr(arg->temp_expand, ' ')
			|| ft_strchr(arg->temp_expand, '\t')))))
		{
			space_var(arg);
			arg->temp_expand = ft_strdup(arg->temp_str);
			free(arg->temp_str);
			arg->temp_str = NULL;
			arg->ex_env = ft_split_origin(arg->temp_expand, ' ');
			arg->str_new = join_2d_arr(arg->str_new, arg->ex_env);
			i = -1;
			while (arg->str_new[++i])
			{
				if ((arg->str_new[i][0] == '\7' && arg->str_new[i][1] == '\6'
					&& arg->str_new[i][2] == '\0') || (arg->str_new[i][0] == '\7'
					&& arg->str_new[i][1] == '\5' && arg->str_new[i][2] == '\0'))
					arg->str_new[i] = 0;
			}
			free2d(arg->ex_env);
		}
		else
			arg->str_new = join2d_with_arr(arg->str_new, arg->temp_expand);
		arg->space = 0;
	}
	else
		arg->str_new = join2d_with_arr(arg->str_new, arg->temp_expand);
}
