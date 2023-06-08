/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:48 by abouram           #+#    #+#             */
/*   Updated: 2023/06/07 01:52:23 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **clean_expand(char **final_expand)
{
	char	*temp;
	int		x;
	int		i;

	x = 0;
	while (final_expand[x])
	{
		i = 0;
		if ((ft_strlen(final_expand[x]) > 1))
		{
			temp = ft_calloc(1,1);
			while (final_expand[x][i])
			{
				temp = ft_strjoin_new(temp ,final_expand[x], i, i);
				i++;
				if (final_expand[x][i] && ft_strchr("3456", final_expand[x][i]))
					i++;
			}
			free(final_expand[x]);
			final_expand[x] = ft_strdup(temp);
			free(temp);
		}
		x++;
	}
	return (final_expand);
}