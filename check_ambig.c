/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:33:28 by abouram           #+#    #+#             */
/*   Updated: 2023/07/23 20:43:34 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_ambig(t_list *my_env, t_myarg *arg, char **s)
{
	while (s[arg->x][++arg->indx])
	{
		if (arg->indx > 0 && s[arg->x][arg->indx] == '$'
			&& s[arg->x][arg->indx - 1] == '\2')
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
	if ((arg->x > 0 && (!ft_strncmp(s[arg->x - 1], ">", 1)
				|| !ft_strncmp(s[arg->x - 1], "<", 2)) && (arg->space == 1
				|| arg->space == 2)))
	{
		arg->tmp = ft_calloc(1, 1);
		arg->tmp = find_in_env_and_alloced(my_env, arg->var, arg->tmp, 0);
		if (arg->tmp && arg->tmp[0] == ' ' && arg->space == 1)
		{
			arg->ambg = 2;
			if (arg->p)
				free(arg->p);
			arg->p = ft_strdup(arg->var);
			global_struct.g_exit_status = 1;
		}
		else if (arg->tmp && arg->tmp[ft_strlen(arg->tmp) - 1] == ' '
			&& arg->space == 2)
		{
			arg->ambg = 2;
			if (arg->p)
				free(arg->p);
			arg->p = ft_strdup(arg->var);
			global_struct.g_exit_status = 1;
		}
		else
		{
			arg->indx = 0;
			while (arg->tmp[arg->indx])
			{
				if (arg->tmp[arg->indx] && arg->tmp[arg->indx] != ' ')
				{
					while (arg->tmp[arg->indx])
					{
						if (arg->tmp[arg->indx] == ' ')
						{
							while (arg->tmp[arg->indx] == ' ')
								arg->indx++;
							if (arg->tmp[arg->indx]
								&& arg->tmp[arg->indx] != ' ')
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
		free(arg->tmp);
	}
}