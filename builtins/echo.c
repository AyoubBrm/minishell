/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:24:44 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/23 12:13:20 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_last_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 2) != 0)
			return (i);
		i++;
	}
	return (i - 1);
}

int	handle_n(char *args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (args[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	my_echo(char **cmd)
{
	int	i;
	int	flag;
	int	blank;

	flag = 0;
	blank = 0;
	i = -1;
	echo_check(cmd, i, &flag, &blank);
	if (!flag && cmd[0])
		handle_n_helper(get_last_args(cmd), cmd, &flag);
	if (!blank)
		printf("\n");
}

void	handle_n_helper(int i, char **cmd, int *flag)
{
	if (*flag)
	{
		while (cmd[i])
		{
			if (!cmd[i + 1])
				printf("%s", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
	else if (!*flag)
	{
		while (cmd[i] && !(ft_strncmp(cmd[i - 1], "-n", 2) == 0))
		{
			if (!cmd[i + 1])
				printf("%s", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
}

void	echo_check(char **cmd, int i, int *flag, int *blank)
{
	while (cmd[++i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0 && !*flag)
		{
			if (!handle_n(cmd[i]) && !cmd[1])
				return ;
			if (handle_n(cmd[i]))
			{
				*flag = 1;
				handle_n_helper(i, cmd, flag);
				break ;
			}
			if (!handle_n(cmd[i]))
				*blank = 1;
		}
		else
		{
			*flag = 1;
			if (!cmd[i + 1])
				printf("%s", cmd[i]);
			else
				printf("%s ", cmd[i]);
		}
	}
}
