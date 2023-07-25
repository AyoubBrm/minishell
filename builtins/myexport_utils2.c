/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myexport_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:36:20 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/24 18:38:08 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_myexport(char *cmd, int i)
{
	if ((cmd[i] >= 32 && cmd[i] <= 47) || (cmd[i] >= 58 && cmd[i] <= 60)
		|| (cmd[i] >= 63 && cmd[i] <= 64) || (cmd[i] >= 91 && cmd[i] <= 94)
		|| (cmd[i] >= 123 && cmd[i] <= 126) || cmd[i] == 96)
	{
		return (1);
	}
	return (0);
}

int	get_equal_pos(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			return (i + 1);
		i++;
	}
	return (ft_strlen(key));
}
