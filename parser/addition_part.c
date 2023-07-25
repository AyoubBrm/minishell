/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_part.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:06:29 by abouram           #+#    #+#             */
/*   Updated: 2023/07/25 16:51:13 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_table	*clean_cmd_and_put_arg(char **str_new, int *i, t_table *new_addition)
{
	if (str_new[*i] && new_addition->cmd && !ft_strchr("<>|", str_new[*i][0])
		&& str_new[*i][0] != '\6')
	{
		if (((str_new[*i] && str_new[*i][0]) && str_new[*i][0] == '\1'))
			ft_memmove(str_new[*i], &str_new[*i][1], ft_strlen(str_new[*i]));
		new_addition->arg = join2d_with_arr(new_addition->arg, str_new[(*i)++]);
	}
	else if (new_addition->cmd && str_new[*i] && str_new[*i][0] == '\0')
		new_addition->arg = join2d_with_arr(new_addition->arg, str_new[(*i)++]);
	return (new_addition);
}

t_table	*addition_append(char **str_new, int *i, t_table *new_addition)
{
	if (str_new[*i] && ft_strncmp(str_new[*i], ">>", 2) == 0)
	{
		new_addition->redirection->type = join2d_with_arr
			(new_addition->redirection->type, str_new[(*i)++]);
		new_addition->redirection->how_many++;
		new_addition->redirection->append_redirection++;
		if ((str_new[*i] && str_new[*i][0] != '|'))
		{
			if (str_new[*i][0] == '\7')
				ft_memmove(str_new[*i], &str_new[*i][1],
					ft_strlen(str_new[*i]));
			new_addition->redirection->file = join2d_with_arr
				(new_addition->redirection->file, str_new[(*i)++]);
		}
		else
		{
			free2d(new_addition->redirection->file);
			new_addition->redirection->file = NULL;
		}
	}
	return (new_addition);
}

t_table	*addition_heredoc(char **str_new, int *i, t_table *new_addition)
{
	if (str_new[*i] && ft_strncmp(str_new[*i], "<<", 2) == 0)
	{
		new_addition->redirection->type = join2d_with_arr
			(new_addition->redirection->type, str_new[(*i)++]);
		new_addition->redirection->heredoc++;
		new_addition->redirection->how_many++;
		if (str_new[*i] && str_new[*i][0] != '|')
		{
			if (str_new[*i] && str_new[*i][0] == '\7')
				ft_memmove(str_new[*i], &str_new[*i][1],
					ft_strlen(str_new[*i]));
			new_addition->redirection->file = join2d_with_arr
				(new_addition->redirection->file, str_new[(*i)++]);
		}
		else
		{
			free2d(new_addition->redirection->file);
			new_addition->redirection->file = NULL;
		}
	}
	return (new_addition);
}

t_table	*addition_pip(char *str_new, int *i, t_table *new_addition)
{
	if (str_new && ft_strncmp("|", str_new, 2) == 0)
	{
		new_addition->pip++;
		new_addition->redirection->pipe = ft_strdup(str_new);
		new_addition->next = ft_calloc(1, sizeof(t_table));
		new_addition = new_addition->next;
		new_addition->redirection = ft_calloc(1, sizeof(t_redirection));
		new_addition->redirection->how_many = 0;
		new_addition->redirection->heredoc = 0;
		new_addition->redirection->out_redirection = 0;
		new_addition->redirection->in_redirection = 0;
		new_addition->redirection->append_redirection = 0;
		new_addition->redirection->type = ft_calloc(1, sizeof(char *));
		new_addition->redirection->file = ft_calloc(1, sizeof(char *));
		new_addition->arg = ft_calloc(1, sizeof(char *));
		(*i)++;
	}
	return (new_addition);
}

t_table	*addition_part(char **str_new, t_table *new_addition)
{
	int	i;

	i = 0;
	while (str_new[i])
	{
		new_addition = addition_pip(str_new[i], &i, new_addition);
		new_addition = addition_heredoc(str_new, &i, new_addition);
		new_addition = addition_append(str_new, &i, new_addition);
		if (str_new[i] && ft_strncmp(">", str_new[i], 1) == 0)
			new_addition = output_rid_and_cmd(str_new, &i, new_addition);
		else if (str_new[i] && ft_strncmp(str_new[i], "<", 1) == 0
			&& str_new[i][1] != '<')
			new_addition = addition_infile(str_new, &i, new_addition);
		else if (str_new[i] && ft_strncmp(str_new[i], "<<", 3) != 0)
			addition_cmd(str_new, &i, new_addition);
		clean_cmd_and_put_arg(str_new, &i, new_addition);
	}
	return (new_addition);
}
