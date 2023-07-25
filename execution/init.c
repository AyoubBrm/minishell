/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:31:04 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 11:52:03 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*my_env;

	(void)av;
	if (ac != 1)
		return (1);
	input = NULL;
	my_env = get_env(env);
	g_global_struct.heredoc_signal = 0;
	g_global_struct.g_exit_status = 0;
	init(input, my_env);
	if (!input)
		return (g_global_struct.g_exit_status);
	return (0);
}

int	init(char *input, t_list	*my_env)
{
	while (1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (g_global_struct.heredoc_signal == 1)
		{
			g_global_struct.g_exit_status = 1;
			g_global_struct.heredoc_signal = 0;
		}
		add_history(input);
		if (input)
			parser_arg(input, &my_env);
		free(input);
		if (!input)
			return (g_global_struct.g_exit_status);
	}
}

int	get_num_pipes(t_table *list)
{
	t_table	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		i += current->pip;
		current = current->next;
	}
	return (i);
}

int	get_num_heredoc(t_table *list)
{
	t_table	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		i += current->redirection->heredoc;
		current = current->next;
	}
	return (i);
}

void	magic(t_table *list, t_list **my_en, t_myarg *arg)
{
	t_list					*my_env;
	t_pipes_n_redirection	*pipes_n_redirection;
	int						i;
	t_table					*current;

	my_env = *my_en;
	pipes_n_redirection = ft_calloc(sizeof(t_pipes_n_redirection), 1);
	init_p(pipes_n_redirection);
	get_utils(pipes_n_redirection, list, *my_en);
	pipes_n_redirection->heredoc = 1;
	i = -1;
	current = list;
	while (current)
	{
		if (pipes_n_redirection->heredoc)
			heredoc(current, my_env, arg, pipes_n_redirection);
		if (heredoc_sig())
			break ;
		if (ambig_check(current, pipes_n_redirection, arg))
			return ;
		exec_pipes(pipes_n_redirection, current, my_en, my_env);
		pipes_n_redirection->pids[++i] = pipes_n_redirection->pid;
		current = current->next;
	}
	exec_helper(pipes_n_redirection);
}
