/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:48 by abouram           #+#    #+#             */
/*   Updated: 2023/05/29 22:34:30 by abouram          ###   ########.fr       */
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
		if ((ft_strlen(final_expand[x]) > 1) || (ft_strlen(final_expand[x]) == 1 && x > 0))
		{
			temp = ft_calloc(1,1);
			while (final_expand[x][i])
			{
				if (ft_strchr("3456", final_expand[x][i]))
					i++;
				temp = ft_strjoin_new(temp ,final_expand[x], i, i);
				i++;
			}
			final_expand[x] = ft_substr(temp, 0, ft_strlen(temp));
			free(temp);
		}
		x++;
	}
	return (final_expand);
}