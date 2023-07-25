/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:21:07 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 05:55:48 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_pos_redirection_v2(int start, char **redirection,
		char *redirection_type)
{
	while (redirection[start])
	{
		if (ft_strncmp(redirection[start], redirection_type,
				ft_strlen(redirection_type) + 1) == 0)
			return (start);
		start++;
	}
	return (0);
}

int	get_pos_redirection(char **redirection, char *redirection_type)
{
	int	i;

	i = 0;
	while (redirection[i])
	{
		if (ft_strncmp(redirection[i], redirection_type,
				ft_strlen(redirection_type) + 1) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	heredoc_which_redirection(char **redirection)
{
	int	i;

	i = 1;
	while (redirection[i])
	{
		if (ft_strncmp(redirection[i], ">", 2) == 0)
			return (1);
		else if (ft_strncmp(redirection[i], ">>", 3) == 0)
			return (2);
		i++;
	}
	return (0);
}

int	is_builtin(char *builtin)
{
	int		i;
	char	*built_ins[7];

	i = 0;
	built_ins[0] = "env";
	built_ins[1] = "export";
	built_ins[2] = "echo";
	built_ins[3] = "cd";
	built_ins[4] = "pwd";
	built_ins[5] = "unset";
	built_ins[6] = "exit";
	while (i < 7)
	{
		if (ft_strncmp(builtin, built_ins[i], ft_strlen(builtin) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}
