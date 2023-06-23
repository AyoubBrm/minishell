/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/06/22 22:51:53 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	*final_addition(char **str_new)
{
	int		i;
	t_table	*new_addition;
	t_table	*head;
	t_table	*head2;

	i = 0;
	new_addition = ft_calloc(1, sizeof(t_table));
	head = new_addition;
	head2 = new_addition;
	new_addition->redirection = ft_calloc(1, sizeof(t_redirection));
	new_addition->redirection->how_many = 0;
	new_addition->redirection->type = ft_calloc(1, sizeof(char *));
	new_addition->redirection->file = ft_calloc(1, sizeof(char *));
	new_addition->pip = 0;
	new_addition->arg = ft_calloc(1, sizeof(char *));
	while (str_new[i])
	{
		if (ft_strncmp("|", str_new[i], 1) == 0)
		{
			new_addition->pip++;
			new_addition->redirection->pipe = ft_strdup(str_new[i]);
			new_addition->next = ft_calloc(1, sizeof(t_table));
			new_addition = new_addition->next;
			new_addition->redirection = ft_calloc(1, sizeof(t_redirection));
			new_addition->redirection->how_many = 0;
			new_addition->redirection->type = ft_calloc(1, sizeof(char *));
			new_addition->redirection->file = ft_calloc(1, sizeof(char *));
			new_addition->arg = ft_calloc(1, sizeof(char *));
			i++;
		}
		else if (ft_strncmp(">", str_new[i], 1) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type,
				str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
			{
				if (str_new[i][0] == '9')
					ft_memmove(str_new[i], &str_new[i][1],
						ft_strlen(str_new[i]));
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file,
					str_new[i++]);
			}
			else
				new_addition->redirection->file = NULL;
		}
		else if (ft_strncmp(str_new[i], "<", 1) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type,
				str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
			{
				if (str_new[i][0] == '9')
					ft_memmove(str_new[i], &str_new[i][1],
						ft_strlen(str_new[i]));
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file,
					str_new[i++]);
			}
			else
				new_addition->redirection->file = NULL;
		}
		else if (ft_strncmp(str_new[i], "<<", 2) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type,
				str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
			{
				if (str_new[i][0] == '9')
					ft_memmove(str_new[i], &str_new[i][1],
						ft_strlen(str_new[i]));
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file,
					str_new[i++]);
			}
			else
				new_addition->redirection->file = NULL;
		}
		else if (ft_strncmp(str_new[i], ">>", 2) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type,
				str_new[i++]);
			new_addition->redirection->how_many++;
			if ((str_new[i] && str_new[i][0] != '|'))
			{
				if (str_new[i][0] == '9')
					ft_memmove(str_new[i], &str_new[i][1],
						ft_strlen(str_new[i]));
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file,
					str_new[i++]);
			}
			else
				new_addition->redirection->file = NULL;
		}
		else
		{
			if (str_new[i] && !new_addition->cmd)
				new_addition->cmd = ft_strdup(str_new[i++]);
			if (str_new[i] && str_new[i][0] && str_new[i][0] != '6'
				&& !new_addition->cmd)
				new_addition->cmd = ft_strdup(str_new[i++]);
			if (str_new[i] && str_new[i][0] && str_new[i][0] == '6')
				i++;
		}
		if (str_new[i] && new_addition->cmd && !ft_strchr("<>|", str_new[i][0])
			&& str_new[i][0] != '6')
		{
			if (((str_new[i] && str_new[i][0]) && (str_new[i][0] == '9'
						|| str_new[i][0] == '1')))
				ft_memmove(str_new[i], &str_new[i][1], ft_strlen(str_new[i]));
			new_addition->arg = join2d_with_arr(new_addition->arg,
				str_new[i++]);
		}
		else if (new_addition->cmd && str_new[i] && str_new[i][0] == '\0')
			new_addition->arg = join2d_with_arr(new_addition->arg,
				str_new[i++]);
	}
	head = error(head);
	if (head == 0)
		return (0);
	new_addition->next = NULL;
	free2d(str_new);
	ambiguous_no_file(head2);
	return (head);
}

char	*find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand,
		int flags)
{
	t_list	*env;

	env = my_env;
	while (env != NULL)
	{
		if (ft_strncmp(&var[1], env->key, ft_strlen(var) + 1) == 0)
		{
			if (flags == 4)
				return (temp_expand = ft_strjoin_new(temp_expand, var, 0,
						ft_strlen(var)));
			else if (flags == 2)
				return (temp_expand = ft_substr(var, 0, ft_strlen(var)));
			if (env->value && (ft_strchr(env->value, '>')
					|| ft_strchr(env->value, '|') || ft_strchr(env->value,
						'<')))
			{
				temp_expand = ft_strjoin(temp_expand, "1");
				temp_expand = ft_strjoin_new(temp_expand, env->value, 0,
					ft_strlen(env->value));
			}
			else
				temp_expand = ft_strjoin_new(temp_expand, env->value, 0,
					ft_strlen(env->value));
		}
		env = env->next;
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
char	**expand(char **s, t_list *my_env, int num_alloc)
{
	int		i;
	int		x;
	int		star;
	char	*var;
	char	*temp_expand;
	char	**ex_env;
	char	**str_new;
	char	*temp_str;
	int		index;

	index = 0;
	str_new = ft_calloc(num_alloc + 1, sizeof(char *));
	x = 0;
	temp_expand = ft_calloc(1, 1);
	while (s[x])
	{
		i = 0;
		while (s[x][i])
		{
			while (s[x][i] == '$' && s[x][i + 1] == '$')
				i++;
			if (s[x][i] == '$' && !ft_strchr2("@*", s[x][i + 1], 2))
			{
				if ((ft_strchr(s[x], '3') || !ft_strchr(s[x], '3')))
				{
					star = i;
					i++;
					while ((ft_isdigit(s[x][i]) || ft_isalpha(s[x][i])
							|| s[x][i] == '_') && !ft_strchr("3456", s[x][i]))
						i++;
					var = ft_substr(s[x], star, i - star);
					if (x > 0 && !ft_strcmp("<<", str_new[x - 1]))
						temp_expand = find_in_env_and_alloced(my_env, var,
							temp_expand, 2);
					else if (s[x][i] == '4')
					{
						temp_expand = find_in_env_and_alloced(my_env, var,
							temp_expand, 4);
						i++;
					}
					else if (s[x][i] && ft_strchr2("\"4", s[x][i + 1], 2))
					{
						star = i;
						while (s[x][i] == '"')
							i++;
						if (s[x][i++] == '4')
							temp_expand = find_in_env_and_alloced(my_env, var,
								temp_expand, 4);
						temp_expand = ft_strjoin_new(temp_expand, s[x], star, i
							- 1);
					}
					else
						temp_expand = find_in_env_and_alloced(my_env, var,
							temp_expand, 0);
					free(var);
				}
			}
			else if ((s[x][i] == '$' && ft_strchr("@*", s[x][i + 1]))
				&& (!ft_strchr2(s[x], '4', i)))
				i += 2;
			else if ((s[x][i] == '$' && ft_strchr("@*", s[x][i + 1]))
				&& (ft_strchr2(s[x], '4', i)))
			{
				star = i;
				while (s[x][i] && s[x][i] != '4')
					i++;
				temp_expand = ft_strjoin_new(temp_expand, s[x], star, i - 1);
			}
			else
			{
				star = i;
				while ((s[x][i] && s[x][i] != '$'))
					i++;
				temp_expand = ft_strjoin_new(temp_expand, s[x], star, i - 1);
			}
		}
		if (((ft_strchr(temp_expand, '6') || ft_strchr(temp_expand, '5'))
				&& (ft_strchr(temp_expand, ' ') || ft_strchr(temp_expand,
						'\t'))))
		{
			if ((ft_strchr(temp_expand, ' ') || ft_strchr(temp_expand, '\t')))
			{
				if (!temp_str)
					temp_str = ft_calloc(1, 1);
				while (ft_strchr(" \t", temp_expand[index]))
					index++;
				while (temp_expand[index])
				{
					while (ft_strchr(" \t", temp_expand[index])
						&& ft_strchr(" \t", temp_expand[index + 1]))
						index++;
					if (ft_strchr(" \t", temp_expand[index]))
					{
						temp_str = ft_strjoin_new(temp_str, temp_expand, index,
							index);
						if (temp_expand[index - 1] && !ft_strchr(" \t",
								temp_expand[0]))
							temp_str = ft_strjoin_new(temp_str, "9", 0, 0);
					}
					else
						temp_str = ft_strjoin_new(temp_str, temp_expand, index,
							index);
					index++;
				}
				temp_expand = ft_strdup(temp_str);
				free(temp_str);
				temp_str = NULL;
			}
			// irintf("%s\n", temp_str);
			ex_env = ft_split_origin(temp_expand, ' ');
			str_new = join_2D_arr(str_new, ex_env);
			free2d(ex_env);
		}
		else
			str_new = join2d_with_arr(str_new, temp_expand);
		ft_bzero(temp_expand, ft_strlen(temp_expand));
		x++;
	}
	free(temp_expand);
	free2d(s);
	return (str_new);
}

void	export(char **s, t_list *my_env, char **env)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] && ft_strncmp(s[x], "echo", 5) == 0)
			my_echo(s);
		x++;
	}
	if (s[0] && ft_strncmp(s[0], "cd", 3) == 0)
	{
		// if (access(s[1], F_OK) == 0)
		// {
		// printf("WTF\n");
		my_cd(s[1], my_env);
		// }
		// else
		// 	printf("cd: %s: No such file or directory\n", s[1]);
	}
	if (s[0] && ft_strncmp(s[0], "pwd", -1) == 0)
		my_pwd();
	if (s[0] && ft_strncmp(s[0], "export", 7) == 0)
		myexport(s, my_env);
	if (s[0] && ft_strncmp(s[0], "env", -1) == 0)
	{
		if (my_env == NULL)
			my_env = get_env(env);
		new_env(my_env);
	}
	if (s[0] && ft_strncmp(s[0], "unset", -1) == 0)
		my_unset(s, my_env);
	// if (s[0] && ft_strncmp(s[0], "exit", -1) == 0)
	// myexit();
}

void	parser_arg(char *input, char **env, t_list *my_env)
{
	t_table	*final_list;
	char	**str;
	char	**s;
	t_myarg	*arg;
	int x = 0;

	arg = malloc(1 * sizeof(t_myarg));
	arg->quote = 0;
	arg->num_alloc = 0;
	// here_doc_expaand(input, arg);
	// printf("%d\n\n\n", arg->exp_heredoc);
	arg->quote = account_quote(input);
	arg->num_alloc = num_alloc_str(input);
	if (arg->quote % 2 == 1)
		printf("%s\n",
			"minishell: syntax error near unexpected token `\"' or `\''");
	else
	{
		str = ft_split(input, '\"');
		s = ft_calloc(sizeof(char *), arg->num_alloc + 1);
		arg->x = 0;
		arg->i = 0;
		arg->index = 0;
		s = get_token_from_str(str, s, arg);
		arg->final_expand = expand(s, my_env, arg->num_alloc);
		// while(final_expand[x])
		// 	printf("%s\n", final_expand[x++]);
		arg->final_expand = clean_expand(arg->final_expand, "3456");
		export(arg->final_expand, my_env, env);
		final_list = final_addition(arg->final_expand);
		x = 0;
		while (final_list)
		{
			printf("_____CMD_____=..%s\n\n", final_list->cmd);
			x = 0;
			while (final_list->arg[x])
				printf("_____ARG_____=..%s\n\n", final_list->arg[x++]);
			printf("_____PIPE_____=..%s\n\n", final_list->redirection->pipe);
			x = 0;
			while (final_list->redirection->type[x])
				printf("_____TYPE_REDI_____=..%s\n\n",
					final_list->redirection->type[x++]);
			x = 0;
			while (final_list->redirection->file[x])
				printf("_____FILE_____=..%s\n\n",
					final_list->redirection->file[x++]);
			final_list = final_list->next;
		}
		free_list(final_list);
	}
}

void	sig_int()
{
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_list	*my_env;
	(void)av;
	my_env = NULL;
	my_env = get_env(env);
	if (ac != 1)
		return (1);
	while (1)
	{
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, &sig_int);
		input = readline("minishell ~$ ");
		add_history(input);
		if (input)
			parser_arg(input, env, my_env);
		free(input);
		// if (!input)
		// 	return (0);
	}
	return (0);

}