/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 18:22:23 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parser_argv3(t_myarg *arg, char *input)
{
	char	**str;
	char	**s;

	arg->p = NULL;
	str = ft_split(input, '\"');
	s = ft_calloc(sizeof(char *), arg->num_alloc + 3);
	arg->x = 0;
	arg->i = 0;
	arg->index = 0;
	arg->space = 0;
	arg->ambg = 0;
	s = get_token_from_str(str, s, arg);
	return (s);
}

void	parser_argv2(t_myarg *arg, char *input)
{
	arg->quote = 0;
	arg->num_alloc = 0;
	here_doc_expaand(input, arg);
	account_quote(input, arg);
	arg->num_alloc = num_alloc_str(input);
	if (arg->quote % 2 == 1)
	{
		ft_printf("%s\n",
			"minishell: unexpected EOF while looking for matching");
		g_global_struct.g_exit_status = 2;
	}
}

void	parser_arg(char *input, t_list **my_env)
{
	t_table		*final_list;
	char		**s;
	t_myarg		*arg;

	(void)my_env;
	arg = ft_calloc(1, sizeof(t_myarg));
	parser_argv2(arg, input);
	if (arg->quote % 2 == 0)
	{
		s = parser_argv3(arg, input);
		arg->final_expand = expand(s, *my_env, arg->num_alloc, arg);
		arg->final_expand = clean_expand(arg->final_expand, "\2\3\4\5\6", arg);
		final_list = final_addition(arg->final_expand, arg);
		if (final_list == NULL)
		{
			free(arg->p);
			free(arg);
			return ;
		}
		final_list->exp_heredoc = arg->exp_heredoc;
		magic(final_list, my_env, arg);
		free_list(final_list);
		free(arg->p);
	}
	free(arg);
}
