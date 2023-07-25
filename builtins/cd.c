/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:25:12 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(char *path, t_list *my_env,
		t_pipes_n_redirection *pipes_n_redirection)
{
	t_list	*current;
	int		home_found;

	current = my_env;
	home_found = 0;
	pipes_n_redirection->exit_builtin = 1;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 4) == 0)
		{
			home_found = 1;
			break ;
		}
		current = current->next;
	}
	current = my_env;
	cd_check(path, &home_found, current);
	return (g_global_struct.g_exit_status);
}

int	cd_check(char *path, int *home_found, t_list *current)
{
	if (path)
	{
		if (chdir(path) != 0)
		{
			ft_printf("bash: cd: %s: No such file or directory\n", path);
			return (g_global_struct.g_exit_status = 1);
		}
	}
	else if (!path && *home_found)
		cd_find_home(current);
	else
	{
		ft_printf("bash: cd: HOME not set\n");
		return (g_global_struct.g_exit_status = 1);
	}
	return (g_global_struct.g_exit_status = 0);
}

void	cd_find_home(t_list *current)
{
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 5) == 0)
		{
			chdir(current->value);
			break ;
		}
		current = current->next;
	}
}
