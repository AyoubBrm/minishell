/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:32:18 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/24 18:33:02 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_export_add(char *cmd, t_list *my_env)
{
	t_my_export	my_export;
	t_list		*current;
	t_list		*new_export;

	new_export = NULL;
	my_export.key = NULL;
	my_export.value = NULL;
	my_export.lol = 0;
	my_export.i = -1;
	my_export.equal = 1;
	my_export.offset = 0;
	current = my_env;
	while (cmd[++my_export.i])
	{
		if ((cmd[my_export.i] == '=') && my_export.equal)
		{
			my_export.offset = 1;
			my_export.equal = 0;
			free_and_alloc_export(cmd, &my_export, current);
			if (!my_export.lol)
				my_export_alloc2(&new_export, &my_env, my_export, cmd);
			my_export.lol = 0;
		}
	}
	my_export_add2(&my_export, cmd, new_export, my_env);
}

void	free_and_alloc_export(char *cmd, t_my_export *my_export,
		t_list *current)
{
	char	*tmp_key;

	free(my_export->key);
	free(my_export->value);
	tmp_key = ft_substr(cmd, 0, my_export->i);
	my_export->key = ft_strdup(tmp_key);
	free(tmp_key);
	my_export->value = ft_strdup(ft_strchr(cmd, '='));
	while (current)
	{
		if (ft_strncmp(current->key, my_export->key, ft_strlen(my_export->key)
				+ 1) == 0)
		{
			my_export_add3(current, my_export->key, my_export->value, cmd);
			my_export->lol = 1;
			break ;
		}
		current = current->next;
	}
}

void	my_export_alloc2(t_list **new_export, t_list **my_env,
		t_my_export my_export, char *cmd)
{
	(*new_export) = malloc(sizeof(t_list));
	(*new_export)->key = ft_strdup(my_export.key);
	(*new_export)->value = ft_strdup(my_export.value);
	(*new_export)->all = ft_strjoin_no_free(my_export.key, ft_strchr_inc(cmd,
				'='));
	free(my_export.key);
	free(my_export.value);
	(*new_export)->next = NULL;
	ft_lstadd_back(my_env, *new_export);
}

void	my_export_add3(t_list *current, char *key, char *value, char *cmd)
{
	if (!current->value)
	{
		free(value);
		value = ft_strchr(cmd, '=');
		current->value = ft_strdup(value);
		current->all = ft_strjoin_no_free(key, current->value);
		free(key);
	}
	else
	{
		free(current->all);
		free(current->value);
		free(value);
		value = ft_strchr(cmd, '=');
		current->value = ft_strdup(value);
		current->all = ft_strjoin_no_free(key, current->value);
		free(key);
	}
}

void	my_export_add2(t_my_export *my_export, char *cmd, t_list *new_export,
		t_list *my_env)
{
	t_list	*current;

	if (!my_export->offset)
	{
		current = my_env;
		while (current)
		{
			if (ft_strncmp(current->key, cmd, ft_strlen(cmd)) == 0)
			{
				my_export->offset = 1;
				break ;
			}
			my_export->offset = 0;
			current = current->next;
		}
		if (!my_export->offset)
		{
			new_export = malloc(sizeof(t_list));
			new_export->key = ft_strdup(cmd);
			new_export->value = NULL;
			new_export->all = NULL;
			new_export->next = NULL;
			ft_lstadd_back(&my_env, new_export);
		}
	}
}
