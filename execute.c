/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/05/15 18:13:17 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_path(char **env)
{
	char **path;
	int i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (env[i] == ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
		{
			path = ft_split(ft_strchr(env[i], '/'), ':');
			return (path);
		}
		i++;
	}
	i = 0;
	while (env[i++])
	{
		path = ft_split(env[i], '=');
		if (ft_strncmp(path[0], "PATH", 4) != 0)
			return (path);
		free2d(path);
	}
	return (path);
}