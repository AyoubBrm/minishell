/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:48 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 12:39:40 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_alloc(char **final_expand, char *str, t_myarg *arg)
{
	free(final_expand[arg->x]);
	final_expand[arg->x] = ft_strdup(arg->temp);
	free(arg->temp);
}

char	**clean_expand(char **final_expand, char *str, t_myarg *arg)
{
	arg->x = 0;
	while (final_expand[arg->x])
	{
		arg->i = 0;
		if ((arg->x > 0 && (ft_strlen(final_expand[arg->x]) > 1))
			|| (arg->x == 0 && !ft_strchr(final_expand[arg->x], '\7')
				&& !ft_strchr(final_expand[arg->x], '\6'))
			|| ((ft_strchr(final_expand[arg->x], '2'))
				|| (ft_strchr(final_expand[arg->x], '\6')
					&& (ft_strlen(final_expand[arg->x]) > 1))))
		{
			arg->temp = ft_calloc(1, 1);
			while (final_expand[arg->x][arg->i])
			{
				if ((final_expand[arg->x][arg->i] && !ft_strchr(str,
						final_expand[arg->x][arg->i])))
					arg->temp = ft_strjoin_new(arg->temp, final_expand[arg->x],
							arg->i, arg->i);
				arg->i++;
			}
			free_and_alloc(final_expand, str, arg);
		}
		arg->x++;
	}
	return (final_expand);
}
