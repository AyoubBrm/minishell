/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:33:28 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_find_space(t_myarg *arg)
{
	while (arg->tmp[arg->indx])
	{
		if (arg->tmp[arg->indx] && !ft_strchr(" \t", arg->tmp[arg->indx]))
		{
			while (arg->tmp[arg->indx])
			{
				if (ft_strchr(" \t", arg->tmp[arg->indx]))
				{
					while (ft_strchr(" \t", arg->tmp[arg->indx]))
						arg->indx++;
					if (arg->tmp[arg->indx] && !ft_strchr(" \t",
							arg->tmp[arg->indx]))
					{
						arg->ambg = 2;
						if (arg->p)
							free(arg->p);
						arg->p = ft_strdup(arg->var);
					}
				}
				arg->indx++;
			}
		}
		if (arg->tmp[arg->indx])
			arg->indx++;
	}
}

void	find_space(t_myarg *arg)
{
	if (arg->tmp && ft_strchr(" \t", arg->tmp[0]) && arg->space == 1)
	{
		arg->ambg = 2;
		if (arg->p)
			free(arg->p);
		arg->p = ft_strdup(arg->var);
		g_global_struct.g_exit_status = 1;
	}
	else if (arg->tmp && ft_strchr(" \t", arg->tmp[ft_strlen(arg->tmp) - 1])
		&& arg->space == 2)
	{
		arg->ambg = 2;
		if (arg->p)
			free(arg->p);
		arg->p = ft_strdup(arg->var);
		g_global_struct.g_exit_status = 1;
	}
	else
	{
		arg->indx = 0;
		continue_find_space(arg);
	}
}

void	check_space(t_myarg *arg, char **s)
{
	while (s[arg->x][++arg->indx])
	{
		if (arg->indx > 0 && s[arg->x][arg->indx] == '$' && s[arg->x][arg->indx
			- 1] == '\2')
			arg->space = 1;
		else if (s[arg->x][arg->indx] == '$')
		{
			while (s[arg->x][arg->indx])
			{
				if (s[arg->x][arg->indx] == '\2')
					arg->space = 2;
				arg->indx++;
			}
			if (!s[arg->x][arg->indx])
				break ;
		}
	}
}

void	check_ambig(t_list *my_env, t_myarg *arg, char **s)
{
	check_space(arg, s);
	if ((arg->x > 0 && (!ft_strncmp(s[arg->x - 1], ">", 1)
				|| !ft_strncmp(s[arg->x - 1], "<", 2)) && (arg->space == 1
				|| arg->space == 2)))
	{
		arg->tmp = ft_calloc(1, 1);
		arg->tmp = find_in_env_and_alloced(my_env, arg->var, arg->tmp, 0);
		find_space(arg);
		free(arg->tmp);
	}
}
