/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:23:17 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 07:43:12 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_helper(t_pipes_n_redirection *pipes_n_redirection)
{
	close_fds(pipes_n_redirection);
	wait_for_children(pipes_n_redirection);
	handle_exit_status(pipes_n_redirection);
	destroy(pipes_n_redirection);
}

void	which_cmd_type(t_pipes_n_redirection *pipes_n_redirection,
		t_table *current)
{
	if (!pipes_n_redirection->abs_path)
	{
		free2d(pipes_n_redirection->path);
		execve(pipes_n_redirection->cmd, pipes_n_redirection->args,
			pipes_n_redirection->env2d);
	}
	else
	{
		free2d(pipes_n_redirection->path);
		execve(current->cmd, pipes_n_redirection->args,
			pipes_n_redirection->env2d);
	}
}

char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (env[i] && env[i] == ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
		{
			path = ft_split_origin(ft_strchr(env[i], '/'), ':');
			return (path);
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		path = ft_split_origin(env[i], '=');
		if (ft_strncmp(path[0], "PATH", 4) != 0)
			return (path);
		free2d(path);
		i++;
	}
	return (path);
}

char	**copy_args_to_2d(char *cmd_path, char **args)
{
	int		i;
	int		total;
	int		cmd_len;
	char	**new_args;
	int		j;

	i = 0;
	total = 0;
	cmd_len = ft_strlen(cmd_path) + 1;
	while (args[i])
	{
		total += ft_strlen(args[i]) + 1;
		i++;
	}
	new_args = ft_calloc(sizeof(char *), (total + cmd_len) + 1);
	new_args[0] = ft_strdup(cmd_path);
	i = 1;
	j = 0;
	while (args[j])
		new_args[i++] = ft_strdup(args[j++]);
	new_args[i] = NULL;
	return (new_args);
}

char	**list_to_double_pointer(t_list *my_env)
{
	t_list		*current;
	char		**new_env;
	int			height;
	int			i;

	current = my_env;
	height = 0;
	while (current)
	{
		height++;
		current = current->next;
	}
	new_env = (char **)ft_calloc(sizeof(char *), (height + 1));
	current = my_env;
	i = -1;
	while (current)
	{
		if (current->value)
			new_env[++i] = ft_strdup(current->all);
		else if (current->key)
			new_env[++i] = ft_strdup(current->key);
		if (current)
			current = current->next;
	}
	return (new_env);
}
