/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:56:20 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 17:58:07 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	destroy(t_pipes_n_redirection *pipes_n_redirection)
{
	free2d(pipes_n_redirection->env2d);
	free2d(pipes_n_redirection->path);
	free2d(pipes_n_redirection->args);
	free(pipes_n_redirection->pids);
	free(pipes_n_redirection->cmd);
	free(pipes_n_redirection->filename);
	free(pipes_n_redirection);
}

void	init_p(t_pipes_n_redirection *pipes_n_redirection)
{
	pipes_n_redirection->filename = NULL;
	pipes_n_redirection->env2d = NULL;
	pipes_n_redirection->path = NULL;
	pipes_n_redirection->args = NULL;
	pipes_n_redirection->pids = NULL;
	pipes_n_redirection->cmd = NULL;
	pipes_n_redirection = NULL;
}

void	get_utils(t_pipes_n_redirection *pipes_n_redirection, t_table *list,
		t_list *my_env)
{
	pipes_n_redirection->env2d = list_to_double_pointer(my_env);
	pipes_n_redirection->path = get_path(pipes_n_redirection->env2d);
	pipes_n_redirection->num_pipes = get_num_pipes(list);
	pipes_n_redirection->pids = ft_calloc(sizeof(int),
			pipes_n_redirection->num_pipes + 1);
}
