/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/06/16 22:20:56 by shmimi           ###   ########.fr       */
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
			path = ft_split_origin(ft_strchr(env[i], '/'), ':');
			return (path);
		}
		i++;
	}
	i = 0;
	while (env[i++])
	{
		path = ft_split_origin(env[i], '=');
		if (ft_strncmp(path[0], "PATH", 4) != 0)
			return (path);
		free2d(path);
	}

	i = 0;

	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
	return (path);
}

char *check_valid_cmd(char *cmd, char **path)
{
	int i = 0;
	char *valid_path;
	char **tmp;

	tmp = ft_split_origin(cmd, ' ');
	while (path[i])
	{
		valid_path = ft_strjoin(path[i], "/");
		valid_path = ft_strjoin(valid_path, tmp[0]);
		if (access(valid_path, F_OK) == 0)
		{
			free2d(tmp);
			return valid_path;
		}
		i++;
	}
	free2d(tmp);
	return 0;
}

char **copy_args_to_2d(char *cmd_path, char **args)
{
	int i = 0;
	int total = 0;
	int cmd_len = ft_strlen(cmd_path) + 1;
	char **new_args;
	while (args[i])
	{
		total += ft_strlen(args[i]) + 1;
		i++;
	}
	new_args = malloc(sizeof(char *) * (total + cmd_len) + 1);

	new_args[0] = ft_strdup(cmd_path);
	i = 1;
	int j = 0;
	while (args[j])
	{
		new_args[i] = ft_strdup(args[j]);
		i++;
		j++;
	}
	new_args[i] = NULL;
	return new_args;
}

char **copy_args_to_2d_redirection(char *filename, char *cmd_path)
{
	char **new_args = malloc(sizeof(char *) * (ft_strlen(filename) + ft_strlen(cmd_path)) + 1);

	new_args[0] = ft_strdup(cmd_path);
	new_args[1] = ft_strdup(filename);
	new_args[2] = NULL;

	return new_args;
}

// void pipes(t_table *current, char **args, char **env2d, char *cmd)
// {

// }

char **list_to_double_pointer(t_list *my_env, t_list *next)
{
	t_list *current = my_env;
	char **new_env;
	int width = 0;
	int height = 0;

	// if (!current)
	// {
	// 	printf("?\n");
	// 	current = next;
	// }

	while (current)
	{
		height++;
		if (current->value)
			width += ft_strlen(current->all) + 1;
		else
			width += ft_strlen(current->key) + 1;
		// if (current->next)
		current = current->next;
	}
	// printf("width %d\n", width);
	// printf("height %d\n", height);

	new_env = malloc(sizeof(char *) * (width * height) + 1);

	if (!current)
		current = next;
	else
		current = my_env;
	int i = 0;

	while (current)
	{
		if (current->value)
			new_env[i] = ft_strdup(current->all);
		else
			new_env[i] = ft_strdup(current->key);
			
		// printf("%s\n", new_env[i]);
		current = current->next;
		i++;
	}
	new_env[i] = NULL;

	return new_env;
}