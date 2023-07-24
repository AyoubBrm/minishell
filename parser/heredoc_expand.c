/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:47:42 by abouram           #+#    #+#             */
/*   Updated: 2023/07/24 01:44:10 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_expaand(char *input, t_myarg *arg)
{
	int	i;

	i = 0;
	arg->exp_heredoc = 0;
	while (input[i])
	{
		if (input && input[i] == '<' && input[i + 1] == '<' && (input[i
					+ 2] == ' ' || input[i + 2] == '\t'))
		{
			i += 2;
			while (input && (input[i] == ' ' || input[i] == '\t'))
				i++;
			while (input[i] && input[i] != '"' && input[i] != '\''
				&& input[i] != ' ' && input[i] != '\t')
				i++;
			if (input[i] == '"' || input[i] == '\'')
				arg->exp_heredoc = 1;
			else
				arg->exp_heredoc = 0;
		}
		if (input[i])
			i++;
	}
}
