/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:26:33 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_exit(char **args, t_pipes_n_redirection *pipes_n_redirection)
{
	int	i;
	int	j;
	int	overflow;

	i = 0;
	j = 1;
	overflow = 0;
	pipes_n_redirection->exit_builtin = 1;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			exit_check(args, i, j);
			j++;
		}
		i++;
		j = 0;
	}
	if (exit_check2(args, overflow))
		return (1);
	exit(g_global_struct.g_exit_status);
}

void	exit_check(char **args, int i, int j)
{
	if (!ft_isdigit(args[i][j]))
	{
		if (args[i][0] == '-')
		{
			j++;
			while (ft_isdigit(args[i][j]) && !ft_isdigit(args[i][j]))
				j++;
			if (!ft_isdigit(args[i][j]) && args[i][j])
			{
				ft_printf("minishell: exit: %s: numeric argument required\n",
					args[i]);
				exit(255);
			}
		}
		j = 1;
		while (args[i][0] == '-' && ft_isdigit(args[i][j]))
		{
			j++;
			if (args[i][j] == '\0')
				exit(255);
		}
		ft_printf("minishell: exit: %s: numeric argument required\n", args[i]);
		exit(255);
	}
}

int	exit_check2(char **args, int overflow)
{
	if (args[0] && args[1])
	{
		printf("minishell: exit: too many arguments\n");
		g_global_struct.g_exit_status = 1;
		return (1);
	}
	else if (args[0])
	{
		if (ft_atoi_origin(args[0]) > 256)
			overflow = ft_atoi_origin(args[0]) - 256;
		else
			overflow = ft_atoi_origin(args[0]);
		g_global_struct.g_exit_status = overflow;
		exit(overflow);
	}
	else
		exit(g_global_struct.g_exit_status);
}
