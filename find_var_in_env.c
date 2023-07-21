/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:36:30 by abouram           #+#    #+#             */
/*   Updated: 2023/07/21 21:51:58 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_status(t_list *env, char *var, char *temp_expand, int flags)
{
	if (flags == 2)
		return (temp_expand = ft_strjoin_new(temp_expand, var, 0, ft_strlen(var)));
	else if (flags == 4)
		return (temp_expand = ft_strjoin_new(temp_expand, var, 0,
				ft_strlen(var)));
	if (flags != 4 && env->value && (ft_strchr(env->value, '>')
			|| ft_strchr(env->value, '|') || ft_strchr(env->value,
				'<')))
	{
		temp_expand = ft_strjoin(temp_expand, "\1");
		temp_expand = ft_strjoin_new(temp_expand, env->value, 0,
				ft_strlen(env->value));
	}
	else
		temp_expand = ft_strjoin_new(temp_expand, env->value, 0,
				ft_strlen(env->value));
	return (temp_expand);
}

char	*find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand,
	int flags)
{
	t_list	*env;

	env = my_env;
	while (env != NULL)
	{
		if (ft_strncmp(&var[1], env->key, ft_strlen(var) + 1) == 0)
			return (temp_expand = expand_status(env, var, temp_expand, flags));
		env = env->next;
	}
	if (ft_strncmp (var,"$?", 3) == 0)
	{
		my_env->ex_status = ft_itoa(global_struct.g_exit_status);
		temp_expand = ft_strjoin(temp_expand, my_env->ex_status);
		free(my_env->ex_status);
		return (temp_expand);
	}
	if (flags == 2)
		return (temp_expand = ft_substr(var, 0, ft_strlen(var)));
	if (flags == 4)
		return (ft_strjoin(temp_expand, var));	
	else if (var[0] == '$' && ft_isdigit(var[1]))
		return (ft_strjoin(temp_expand, &var[2]));
	else if ((ft_strchr(var, '$') && ft_strlen(var) == 1))
		return (ft_strjoin(temp_expand, var));
	return (temp_expand);
}
