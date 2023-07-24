/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_with_2Darr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:42:05 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:44:15 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**join_2d_arr(char **str1, char **str2)
{
	int		i;
	int		j;
	char	**new_expand;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (NULL);
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	new_expand = ft_calloc((i + j) + 2, sizeof(char *));
	if (!new_expand)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		new_expand[i] = ft_strdup(str1[i]);
	while (str2[++j])
		new_expand[i++] = ft_strdup(str2[j]);
	free2d(str1);
	return (new_expand);
}
