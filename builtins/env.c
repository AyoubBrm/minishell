/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:25:43 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/23 13:11:56 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_env(char **env)
{
	int		i;
	t_list	*current;
	t_list	*new_env;
	t_list	*head;
	char	**env_old;

	i = -1;
	current = NULL;
	new_env = NULL;
	env_old = NULL;
	while (env[++i])
	{
		env_alloc(&new_env, env_old, env[i]);
		if (current == NULL)
		{
			head = new_env;
			current = head;
		}
		else
		{
			current->next = new_env;
			current = current->next;
		}
	}
	return (head);
}

void	new_env(t_list **my_env)
{
	t_list	*current;

	current = *my_env;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	env_alloc(t_list **new_env, char **env_old, char *envi)
{
	env_old = ft_split_origin(envi, '=');
	*new_env = ft_calloc(sizeof(t_list), 1);
	(*new_env)->key = NULL;
	(*new_env)->value = NULL;
	(*new_env)->all = NULL;
	(*new_env)->key = ft_strdup(env_old[0]);
	(*new_env)->value = ft_strdup(env_old[1]);
	free2d(env_old);
	(*new_env)->all = ft_strjoin_no_free((*new_env)->key, ft_strchr_inc(envi,
				'='));
	(*new_env)->next = NULL;
}
