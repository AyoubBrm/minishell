/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:29:36 by abouram           #+#    #+#             */
/*   Updated: 2023/06/25 23:14:09 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_after_dollar(t_myarg *arg, char **s)
{
	if ((s[arg->x][arg->i] == '$' && ft_strchr("@*", s[arg->x][arg->i + 1]))
		&& (!ft_strchr2(s[arg->x], '\4', arg->i)))
		arg->i += 2;
	else if ((s[arg->x][arg->i] == '$' && ft_strchr("@*", s[arg->x][arg->i
			+ 1])) && (ft_strchr2(s[arg->x], '\4', arg->i)))
	{
		arg->star = arg->i;
		while (s[arg->x][arg->i] && s[arg->x][arg->i] != '\4')
			arg->i++;
		arg->temp_expand = ft_strjoin_new(arg->temp_expand, s[arg->x],
				arg->star, arg->i - 1);
	}
	else
	{
		arg->star = arg->i;
		while ((s[arg->x][arg->i] && s[arg->x][arg->i] != '$'))
			arg->i++;
		arg->temp_expand = ft_strjoin_new(arg->temp_expand, s[arg->x],
				arg->star, arg->i - 1);
	}
}

void	expand_inside_quote(char **s, t_myarg *arg, t_list *my_env)
{
	arg->var = ft_substr(s[arg->x], arg->star, arg->i - arg->star);
	if (arg->x > 0 && !ft_strncmp("<<", arg->str_new[arg->x - 1], 3))
		arg->temp_expand = find_in_env_and_alloced(my_env, arg->var,
				arg->temp_expand, 2);
	else if (s[arg->x][arg->i] == '\4')
	{
		arg->temp_expand = find_in_env_and_alloced(my_env, arg->var,
				arg->temp_expand, 4);
		arg->i++;
	}
	else if (s[arg->x][arg->i] && ft_strchr2("\"\4", s[arg->x][arg->i + 1], 2))
	{
		arg->star = arg->i;
		while (s[arg->x][arg->i] == '"')
			arg->i++;
		if (s[arg->x][arg->i++] == '\4')
			arg->temp_expand = find_in_env_and_alloced(my_env, arg->var,
					arg->temp_expand, 4);
		arg->temp_expand = ft_strjoin_new(arg->temp_expand, s[arg->x],
				arg->star, arg->i - 1);
	}
	else
		arg->temp_expand = find_in_env_and_alloced(my_env, arg->var,
				arg->temp_expand, 0);
	free(arg->var);
}

void	expand2(char **s, t_list *my_env, t_myarg *arg)
{
	if (s[arg->x][arg->i] == '$' && !ft_strchr2("@*", s[arg->x][arg->i + 1], 2))
	{
		if ((ft_strchr(s[arg->x], '\3') || !ft_strchr(s[arg->x], '\3')))
		{
			arg->star = arg->i;
			arg->i++;
			while ((ft_isdigit(s[arg->x][arg->i])
				|| ft_isalpha(s[arg->x][arg->i])
				|| s[arg->x][arg->i] == '_') && !ft_strchr("\3\4\5\6",
				s[arg->x][arg->i]))
				arg->i++;
			expand_inside_quote(s, arg, my_env);
		}
	}
}

char	**expand(char **s, t_list *my_env, int num_alloc, t_myarg *arg)
{
	arg->index = 0;
	arg->str_new = ft_calloc(num_alloc + 1, sizeof(char *));
	arg->x = 0;
	arg->temp_expand = ft_calloc(1, 1);
	while (s[arg->x])
	{
		arg->i = 0;
		while (s[arg->x][arg->i])
		{
			while (s[arg->x][arg->i] == '$' && s[arg->x][arg->i + 1] == '$')
				arg->i++;
			expand2(s, my_env, arg);
			skip_after_dollar(arg, s);
		}
		expand_inside_env_or_dont_expand(arg);
		ft_bzero(arg->temp_expand, ft_strlen(arg->temp_expand));
		arg->x++;
	}
	free(arg->temp_expand);
	free2d(s);
	return (arg->str_new);
}
