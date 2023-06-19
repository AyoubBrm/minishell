/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_with_2Darr_with_1Darr.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:31:30 by abouram           #+#    #+#             */
/*   Updated: 2023/06/19 01:36:10 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join2d_with_arr(char **str1, char *str2)
{
	int		i;
	char	**new_expand;

	i = 0;
	if (!str1 && !str2)
		return (NULL);
	while (str1[i])
		i++;
	new_expand = ft_calloc((i + 1) + 1, sizeof(char *));
	if (!new_expand)
		return (NULL);
	i = -1;
	while (str1[++i])
		new_expand[i] = ft_strdup(str1[i]);
	new_expand[i] = ft_strdup(str2);
	free2d(str1);
	return (new_expand);
}
