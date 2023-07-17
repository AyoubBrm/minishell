/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/17 19:30:48 by shmimi           ###   ########.fr       */
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
		if (env[i] && env[i] == ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
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
	char *valid_cmd;

	while (path[i])
	{
		valid_path = ft_strjoin(path[i], "/");
		if (cmd)
			valid_cmd = ft_strjoin(valid_path, cmd);
		if (access(valid_cmd, F_OK) == 0)
		{
			free(valid_path);
			return valid_cmd;
		}
		if (cmd)
			free(valid_cmd);
		free(valid_path);
		i++;
	}
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
	new_args = ft_calloc(sizeof(char *), (total + cmd_len) + 1);

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

char **list_to_double_pointer(t_list *my_env)
{
	t_list *current = my_env;
	char **new_env;
	int width = 0;
	int height = 0;

	while (current)
	{
		// printf("%s\n", current->all);
		height++;
		if (current->value)
			width += ft_strlen(current->all) + 1;
		else if (current->key)
			width += ft_strlen(current->key) + 1;
		// if (current->next)
		current = current->next;
	}
	// printf("width %d\n", width);
	// printf("height %d\n", height);

	new_env = malloc(sizeof(char *) * (width * height) + 1);

	current = my_env;
	int i = 0;

	while (current)
	{
		if (current->value)
			new_env[i] = ft_strdup(current->all);
		else if (current->key)
			new_env[i] = ft_strdup(current->key);

		// printf("%s\n", new_env[i]);
		if (current)
			current = current->next;
		i++;
	}
	new_env[i] = NULL;

	return new_env;
}

void execute_cmds(t_table *current, t_pipes_n_redirection *pipes_n_redirection, t_list *my_env, int g_exit_status)
{
	if (is_builtin(current->cmd))
	{
		if (current->cmd && !current->arg[0] && ft_strncmp(current->cmd, "export", 7) == 0)
			myexport(current->arg, my_env);
		else if (current->cmd && ft_strncmp(current->cmd, "env", 4) == 0)
		{
			if (!my_env)
				printf("???\n");
			new_env(&my_env);
		}
		else if (current->cmd && ft_strncmp(current->cmd, "echo", 5) == 0)
			my_echo(current->arg, g_exit_status);
		else if (current->cmd && ft_strncmp(current->cmd, "pwd", 4) == 0)
			my_pwd();
	}
	else
	{
		if (!pipes_n_redirection->abs_path)
		{
			free2d(pipes_n_redirection->path);
			execve(pipes_n_redirection->cmd, pipes_n_redirection->args, pipes_n_redirection->env2d);
		}
		else
		{
			free2d(pipes_n_redirection->path);
			execve(current->cmd, pipes_n_redirection->args, pipes_n_redirection->env2d);
		}
	}
	exit(0);
}

void child(t_table *current, t_pipes_n_redirection *pipes_n_redirection, t_list *my_env, int g_exit_status)
{
	int i = 0;
	/****************************************************** Handle all redirections **********************************************/
	all_redirections(current, pipes_n_redirection);
	/****************************************************** End redirections********** **********************************************/
	/****************************************************** Get cmd path and args **********************************************/
	if (current->cmd || current->cmd[0])
	{
		free(pipes_n_redirection->cmd);
		free2d(pipes_n_redirection->args);
		pipes_n_redirection->cmd = check_valid_cmd(current->cmd, pipes_n_redirection->path);
		pipes_n_redirection->args = copy_args_to_2d(current->cmd, current->arg);
	}
	/****************************************************** End cmd path and args **********************************************/
	/******************************************** Check for cmd permissions and existence *******************************************/
	no_such_file(current, pipes_n_redirection, g_exit_status, i);
	/***************************** END checking for cmd permissions and existence ******************************/
	if (access(current->cmd, F_OK | X_OK) == 0)
		pipes_n_redirection->abs_path = 1;
	dup2(pipes_n_redirection->in, 0);
	if (current->pip)
	{
		dup2(pipes_n_redirection->pipefds[1], 1);
		close(pipes_n_redirection->pipefds[0]);
		close(pipes_n_redirection->pipefds[1]);
	}
	/****************************************************** Handle all redirections **********************************************/
	all_redirections(current, pipes_n_redirection);
	/****************************************************** End redirections********************************************************/
	/****************************************************** Execute CMDs ******************************************************/
	execute_cmds(current, pipes_n_redirection, my_env, g_exit_status);
}

void parent(t_table *current, t_pipes_n_redirection *pipes_n_redirection, t_list *my_env, int g_exit_status)
{
	if (current->cmd && current->arg[0] && ft_strncmp(current->cmd, "export", 7) == 0)
		myexport(current->arg, my_env);
	else if (current->cmd && ft_strncmp(current->cmd, "unset", 6) == 0 && !current->pip)
		my_unset(current->arg, &my_env);
	else if (current->cmd && ft_strncmp(current->cmd, "exit", 5) == 0)
	{
		if (!pipes_n_redirection->num_pipes)
			my_exit(current->arg, g_exit_status);
	}
	else if (current->cmd && ft_strncmp(current->cmd, "cd", 3) == 0)
	{
		if (!pipes_n_redirection->num_pipes)
			g_exit_status = my_cd(current->arg[0], my_env);
	}
	else if (current->arg[0] && ft_strncmp(current->arg[0], "*", 2) == 0)
		wildcard_helper(pipes_n_redirection);
	close(pipes_n_redirection->pipefds[1]); // close write end of pipe
	if (pipes_n_redirection->in != 0)
		close(pipes_n_redirection->in);						   // close input when it's not 0 (STDIN fd) (usually it points to read end of pipe)
	pipes_n_redirection->in = pipes_n_redirection->pipefds[0]; // Save input of the previous cmd
															   // dup2(pipes_n_redirection->out, 1);
}