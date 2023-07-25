/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:26:01 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 18:51:08 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_export_alloc(t_list **my_export, t_list *current, int b, int k)
{
	(*my_export)->value = malloc(ft_strlen(current->value) + 4);
	(*my_export)->value[0] = '=';
	(*my_export)->value[1] = '"';
	while (k < ft_strlen(current->value) + 2)
	{
		(*my_export)->value[k] = current->value[b];
		k++;
		b++;
	}
	(*my_export)->value[k] = '"';
	k++;
	(*my_export)->value[k] = '\0';
	(*my_export)->key_exp = ft_strjoin_no_free("declare -x ",
			(*my_export)->key);
	(*my_export)->all = ft_strjoin_no_free((*my_export)->key_exp,
			(*my_export)->value);
	(*my_export)->next = NULL;
	printf("%s\n", (*my_export)->all);
}

int	my_export_check2(char *cmd, t_pipes_n_redirection *pipes_n_redirection)
{
	int		j;
	char	*key;

	j = 0;
	key = ft_substr(cmd, 0, get_equal_pos(cmd));
	while (key[j] && key)
	{
		if (check_myexport(key, j))
		{
			ft_printf("bash: not a valid identifiers\n");
			g_global_struct.g_exit_status = 1;
			pipes_n_redirection->exit_builtin = 1;
			free(key);
			return (1);
		}
		j++;
	}
	free(key);
	return (0);
}

void	print_export(char **cmd, t_list *my_env)
{
	t_list	*current;
	t_list	*my_export;
	int		k;
	int		b;

	my_export = malloc(sizeof(t_list));
	current = my_env;
	if (!cmd[0])
	{
		while (current)
		{
			k = 2;
			b = 0;
			my_export->key = ft_strdup(current->key);
			if (current->value)
				my_export_alloc(&my_export, current, b, k);
			else
				printf("declare -x %s\n", my_export->key);
			current = current->next;
		}
	}
	free(my_export);
}

void	myexport(char **cmd, t_list *my_env,
		t_pipes_n_redirection *pipes_n_redirection)
{
	int		i;
	int		j;
	char	*value;
	int		flag;

	i = -1;
	j = 0;
	value = NULL;
	flag = 0;
	print_export(cmd, my_env);
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (my_export_check3(pipes_n_redirection, cmd[i], &flag, j))
				break ;
			j++;
		}
		if (!flag)
			my_export_add(cmd[i], my_env);
		flag = 0;
	}
	if (!pipes_n_redirection->exit_builtin)
		pipes_n_redirection->exit_builtin = 0;
}

int	my_export_check3(t_pipes_n_redirection *pipes_n_redirection, char *cmd,
		int *flag, int j)
{
	if (my_export_check2(cmd, pipes_n_redirection))
	{
		*flag = 1;
		return (1);
	}
	if (ft_isdigit(cmd[0]) || !ft_isalpha(cmd[0]))
	{
		if (cmd[0] == '_')
			return (1);
		ft_printf("bash: not a valid identifierss\n");
		g_global_struct.g_exit_status = 1;
		pipes_n_redirection->exit_builtin = 1;
		*flag = 1;
		return (1);
	}
	if ((cmd[j] == '+' && cmd[j + 1] == '+'))
	{
		ft_printf("bash: not a valid identifier\n");
		g_global_struct.g_exit_status = 1;
		pipes_n_redirection->exit_builtin = 1;
		*flag = 1;
		return (1);
	}
	return (0);
}
