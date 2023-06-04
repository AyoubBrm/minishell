/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/06/04 01:54:05 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join2d_with_arr(char **str1, char *str2)
{
	int i;
	char **new_expand;
	
	i = 0;
	if (!str1 && !str2)
		return (NULL);
	while(str1[i])
		i++;
	new_expand = ft_calloc((i + 1) + 1, sizeof(char *));
	if (!new_expand)
		return (NULL);
	i = -1;
	while(str1[++i])
		new_expand[i] = ft_strdup(str1[i]);
	if (str2[0] == '1')
		new_expand[i] = ft_strdup(&str2[1]);
	else
		new_expand[i] = ft_strdup(str2);
	free2d(str1);
	return(new_expand);
}

char	**ft_expand(char **str1, char **str2)
{
	int i;
	int j;
	char **new_expand;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (NULL);
	while(str2[j])
		j++;
	while(str1[i])
		i++;
	new_expand = ft_calloc((i + j) + 1, sizeof(char *));
	if (!new_expand)
		return (NULL);
	i = -1;
	j = -1;
	while(str1[++i])
		new_expand[i] = ft_strdup(str1[i]);
	while(str2[++j])
		new_expand[i + j] = ft_strdup(str2[j]);
	free2d(str1);
	return(new_expand);
}
void final_addition(char **str_new)
{
	int i;
	i = 0;
	int x = 0;
	t_table *new_addition;
	t_table *head;

	new_addition		= ft_calloc(1, sizeof(t_table));
 	head = new_addition;	
	new_addition->redirection	 = ft_calloc(1, sizeof(t_redirection));
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
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type, str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file, str_new[i++]);
		}
		else if (ft_strncmp(str_new[i], "<", 1) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type, str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file, str_new[i++]);
		}
		else if (ft_strncmp(str_new[i], "<<", 2) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type, str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file, str_new[i++]);
		}
		else if (ft_strncmp(str_new[i], ">>", 2) == 0)
		{
			new_addition->redirection->type = join2d_with_arr(new_addition->redirection->type, str_new[i++]);
			new_addition->redirection->how_many++;
			if (str_new[i] && str_new[i][0] != '|')
				new_addition->redirection->file = join2d_with_arr(new_addition->redirection->file, str_new[i++]);
		}
		else 
		{
			if (!new_addition->cmd && str_new[i][0] == 0)
				new_addition->cmd = ft_strdup(str_new[i++]);
			if (!new_addition->cmd && !ft_strchr("<>|", str_new[i][0]))
				new_addition->cmd = ft_strdup(str_new[i++]);
			if (new_addition->cmd[0] == '1')
				new_addition->cmd = ft_strdup(&new_addition->cmd[1]);
		}
		if (str_new[i] && new_addition->cmd && !ft_strchr("<>|", str_new[i][0]))
			new_addition->arg = join2d_with_arr(new_addition->arg, str_new[i++]);
		else if (new_addition->cmd && str_new[i] && str_new[i][0] == '\0')
			new_addition->arg = join2d_with_arr(new_addition->arg, str_new[i++]);
	}
	new_addition->next = NULL;
	free2d(str_new);
	x = 0;
	t_table *a;
	a = head;
	while (head)
	{
		printf("_____CMD_____=..%s\n\n", head->cmd);
		x = 0;
		while (head->arg[x])
			printf("_____ARG_____=..%s\n\n", head->arg[x++]);
			printf("_____PIPE_____=..%d\n\n", head->pip);
			printf("_____manyred.._____=..%d\n\n", head->redirection->how_many);
		x = 0;
		while (head->redirection->type[x])
		{
			if 	(head->redirection->type[x] && ft_strncmp("<<", head->redirection->type[x], 3) && ft_strncmp(">>", head->redirection->type[x], 3)
				&& ft_strncmp("<", head->redirection->type[x], 3) && ft_strncmp(">", head->redirection->type[x], 2)
				&& ft_strncmp("|", head->redirection->type[x], 3))
				{
					if (!ft_strncmp(">>", head->redirection->type[x], 2) || !ft_strncmp("<<", head->redirection->type[x], 2))
						printf("syntax error near unexpected token `%c%c'\n", head->redirection->type[x][2],head->redirection->type[x][3]);
					free_list(head);
					return ;
				}
			if (ft_strncmp(head->redirection->type[x], ">>" ,3) != 0)
				{
					printf("syntax error near unexpected token ,%c\n",  head->redirection->file[x][2]);
					// free_list(head);
					return;
				}
			if (head->redirection->type[x] && !head->redirection->file[x])
				printf("syntax error near unexpected token `newline'\n");
			printf("_____REDIRECTION_____=..%s\n\n", head->redirection->type[x]);
			x++;
		}
		if((head->redirection->pipe && ft_strncmp("||", head->redirection->pipe, 2) == 0)
			|| (!head->cmd && head->pip == 1))
		{
			if(ft_strlen(head->redirection->pipe) == 1 && !head->next->cmd)
				printf("syntax error near unexpected token `|'\n");
			else if(head->redirection->pipe && ft_strncmp("||", head->redirection->pipe, 2) == 0)
				printf("syntax error near unexpected token `||'\n");
			else if ((!head->cmd && head->pip == 1))
				printf("syntax error near unexpected token `|'\n");
			free_list(head);
			return ;
		}
		x = 0;
		while (head->redirection->file[x])
			printf("_____FILE_____=..%s\n\n", head->redirection->file[x++]);
		printf("_____PIPE_____=..%s\n\n", head->redirection->pipe);
		head = head->next;
	}
	head = a;
	// free_list(head);
}

char	*find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand, int flags)
{
	t_list *env;
	env = my_env;
	while(env != NULL)
	{
		if (ft_strncmp(&var[1], env->key,  ft_strlen(var) + 1) == 0)
		{
			if (flags == 4)
				return(temp_expand = ft_strjoin_new(temp_expand, var, 0, ft_strlen(var)));
			else
				temp_expand = ft_strjoin_new(temp_expand, env->value, 0, ft_strlen(env->value));
		}
		env = env->next;
	}
	if(flags == 4)
		return(ft_strjoin(temp_expand, var));
	else if (var[0] == '$' && ft_isdigit(var[1]))
		return(ft_strjoin(temp_expand, &var[2]));
	else if(ft_strchr(var, '$') && ft_strlen(var) == 1)
		return(ft_strjoin(temp_expand, var));
	return(temp_expand);
}
char	**expand(char **s, t_list *my_env, int num_alloc)
{
	int		i;
	int		x;
	int		star;
	char	*var;
	char	*temp_expand;
	char 	**ex_env;
	char	**str_new;
	char	*temp_str;
	int index;
	
	str_new = ft_calloc(num_alloc + 1 , sizeof(char *));
	x = 0;
	while (s[x])
	{
		temp_expand = ft_calloc(1, 1);
		i = 0;
		while (s[x][i])
		{
			while (s[x][i] == '$' && s[x][i + 1] == '$')
				i++;
			if (s[x][i] == '$' && !ft_strchr2("@*", s[x][i + 1], 2))
			{
				if ((ft_strchr(s[x] ,'3') || !ft_strchr(s[x] ,'3')))
				{
					star = i;
					i++;
					while ((ft_isdigit(s[x][i]) || ft_isalpha(s[x][i]) || s[x][i] == '_') && !ft_strchr("3456", s[x][i]))
						i++;
					var = ft_substr(s[x], star, i - star);
					if(s[x][i] == '4')
					{
						temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 4);
						i++;
					}
					else if (s[x][i] && ft_strchr2("\"4", s[x][i + 1], 2))
					{
						star = i;
						while(s[x][i] == '"')
							i++;
						if (s[x][i++] == '4')
							temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 4);
						temp_expand = ft_strjoin_new(temp_expand, s[x], star, i - 1);
					}
					else 
						temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 0);
					free(var);
				}
			}
			else if ((s[x][i] == '$' && ft_strchr("@*", s[x][i + 1])) && (!ft_strchr2(s[x], '4', i)))
				i += 2;
			else if ((s[x][i] == '$' && ft_strchr("@*", s[x][i + 1])) && (ft_strchr2(s[x], '4', i)))
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
			&& (ft_strchr(temp_expand, ' ') || ft_strchr(temp_expand, '\t'))))
		{
			if ((ft_strchr(temp_expand, ' ') || ft_strchr(temp_expand, '\t')))
			{
				index = 0;
				if (!temp_str)
					temp_str = ft_calloc (1 ,1);
				while(temp_expand[index])
				{
					while (temp_expand[index] == ' ' && temp_expand[index + 1] == ' ')
						index++;
					if (temp_expand[index] == ' ')
					{
						temp_str = ft_strjoin_new(temp_str, temp_expand, index, index);
						temp_str = ft_strjoin_new(temp_str, "9", 0, 0);
					}
					else
						temp_str = ft_strjoin_new(temp_str, temp_expand, index, index);
					index++;
				}
				temp_expand = ft_substr(temp_str, 0, ft_strlen(temp_str));
			}
			ex_env = ft_split_origin(temp_expand, ' ');
			str_new = ft_expand(str_new, ex_env);
			free2d(ex_env);
			free(temp_str);
		}
		else
		{
			while (str_new[x])
				x++;
			str_new[x] = ft_substr(temp_expand, 0, ft_strlen(temp_expand));
		}
		free(temp_expand);
		temp_expand = NULL;
		x++;
	}
	free2d(s);
	return(str_new);
}

void export(char **s, t_list *my_env, char **env)
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
void parser_arg(char *input, char **env, t_list *my_env)
{
	size_t	x;
	size_t	i = 0;
	char	**str;
	char	**s;
	int		index = 0;
	int		num_alloc = 0;
	int		quote;
	int		star = 0;
	char	**final_expand;
	quote = account_quote(input);
	x = 0;
	i = 0;
	while (input[x])
	{
		if (input[x] != '"' && input[x] != '\'') // this for allocte the string **str
		{
			while (input[x] == ' ' && input[x])
					x++;
			while (input[x] && !ft_strchr2(" \"'><|", input[x], 6) && !ft_strchr2(" \"'", input[x + 1], 3))
					x++;
			if ((!ft_strchr2(" \"'><|", input[x], 6) && ft_strchr2(" 	", input[x], 2))
				|| (!ft_strchr2(" \"'><|", input[x], 6) && input[x + 1] == '\0')
				|| (!ft_strchr2(" \"'><|", input[x], 6) && input[x + 1] == '"'))
				num_alloc++;
			while (!ft_strchr2(" \"'><|", input[x], 6) && input[x])
				x++;
		}
		if (input[x] == '>' || input[x] != '|' || input[x] != '<')
		{
			num_alloc++;
			if((input[x] == '>' && input[x + 1] == '>') || (input[x] == '<' && input[x + 1] == '<'))
				x += 2;
			if (input[x] == '>' && input[x + 1])
				num_alloc++;
			num_alloc++;
		}
		if (input[x] == '"')
		{
			if (input[x] == '"' && input[x])
				x++;
			while (input[x] != '"' && input[x])
				x++;
			if (input[x] == '"' )
			{
				num_alloc++;
				x++;
			}	
		}
		if (input[x] == '\'')
		{
			if (input[x] == '\'' && input[x])
				x++;
			while (input[x] != '\'' && input[x])
				x++;
			if (input[x] == '\'')
			{
				num_alloc++;
				x++;
			}	
		}
		x++;
	}
	if (quote % 2 == 1)
			printf("%s\n", "minishell: syntax error near unexpected token `\"' or `\''");
	else
	{
		str = ft_split(input, '\"');
		s = ft_calloc(sizeof(char *) , num_alloc + 1);
		x = 0;
		while (str[x])
		{
			if (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
			{
				while (str[x][i] && ft_strchr(" \t", str[x][i]))
					i++;
				if (i > 0 && x > 0 && ft_strchr2(" 	", str[x][i - 1], 2))
					index++;
				if (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
				{
					star = i;
					while (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
					{	
						if ((str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '"')
							|| (str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '\''))
						{
							if (!s[index])
								s[index] = ft_calloc(1, 1);
							s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
							x++;
							i = 0;
							star = 0;
							while(str[x][i] && !ft_strchr2("\'\" \t", str[x][i], 4))
								i++;
							s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
						}
						else
						{
							if (!s[index])
								s[index] = ft_calloc(1, 1);
							while(str[x][i] && !ft_strchr2("\'\" \t$><|", str[x][i], 8))
								i++;
							if ((str[x] && str[x][i] == '$' && str[x][i + 1]) || (str[x] && str[x][i] == '$' && str[x][i + 1] == '\0' && !str[x + 1]))
							{
								i++;
								while ((str[x][i] && !ft_strchr2("\t $><|", str[x][i], 6)))
									i++;
								s[index] = ft_strjoin_new(s[index], str[x],star, i - 1);
								if ((str[x + 1] && !ft_strchr2(" \t", str[x][i], 2) && str[x + 1][0] == '"' && str[x + 1][1] == '"')
									|| (x > 0 && !ft_strchr2(" \t", str[x][i], 2) && str[x - 1][0] == '"' && str[x - 1][1] == '"')
									|| (str[x + 1] && !ft_strchr2(" \t", str[x][i], 2) && str[x + 1][0] == '\'' && str[x + 1][1] == '\'')
									|| (x > 0 && !ft_strchr2(" \t", str[x][i], 2) && str[x - 1][0] == '\'' && str[x - 1][1] == '\''))
										s[index] = ft_strjoin_new(s[index], "5", 0, 1);
								else
									s[index] = ft_strjoin_new(s[index], "6", 0, 0);
							}
							else
								s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
							if (ft_strchr2(" \t", str[x][i], 2))
								index++;
							while (ft_strchr2(" \t", str[x][i], 2))
								i++;	
							if (str[x][i] && ft_strchr2("<>|", str[x][i], 3))
							{
								if ((i > 0 && !ft_strchr2(&str[x][0], ' ', i) && !ft_strchr2(&str[x][0], '\t', i))
									|| (x > 0 && i == 0 ))
									index++;
								else if (i > 0 && str[x][i - 1] && !ft_strchr2(" \t", str[x][i - 1], 2))
									index++;
								star = i;
								if (!s[index])
									s[index] = ft_calloc(1, 1);
								while (str[x][i] && ft_strchr2("<>|", str[x][i], 3))
										i++;
									s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
								if (!ft_strchr("\t ", str[x][i]) && str[x][i])
									index++;
								else if (!ft_strchr2(&str[x][i], ' ', ft_strlen(str[x]) - i)
									&& (!ft_strchr2(&str[x][i], '\t', ft_strlen(str[x]) - i)) && str[x + 1])
									index++;
								if (!s[index])
									s[index] = ft_calloc(1, 1);
							}
							star = i;
						}
					}
				}
			}
			if (((((str[x][0] == '"' && str[x][1] == '"') || (str[x][0] == '\'' && str[x][1] == '\''))
				&& (x == 0 && str[x + 1])) && ft_strchr(" \t", str[x + 1][0])))
					s[index] = ft_calloc(1,1);	
			if (((((str[x][0] == '"' && str[x][1] == '"') || (str[x][0] == '\'' && str[x][1] == '\''))
				&& (str[x + 1] && str[x - 1])) && ft_strchr(" \t", str[x + 1][0])
				&& ft_strchr(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1])))
					s[index] = ft_calloc(1,1);
			if (((str[x][0] == '"' && str[x][1] == '"') || ((str[x][0] == '\'' && str[x][1] == '\'')))
				&& !str[x + 1] && str[x - 1] && ft_strchr(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1]))
					s[index] = ft_calloc(1,1);
			if (((str[0][0] == '"' && str[0][1] == '"') || ((str[0][0] == '\'' && str[0][1] == '\'')))
				&& !str[1])
					s[index] = ft_calloc(1,1);
			if (str[x][i] == '"' && str[x][i + 1] != '"')
			{
				i++;
				star = i;
				while (str[x][i] && !ft_strchr2("$|><\"", str[x][i], 5))
					i++;
				if (str[x][i] == '$')
				{
					while (str[x][i] == '$')
						i++;
					while (str[x][i] && str[x][i] != '"')
						i++;
					if (str[x][i] == '"')
					{
						if (!s[index])
							s[index] = ft_calloc(1, 1);
						s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
					}
					s[index] = ft_strjoin_new(s[index], "3", 0, 0);
				}
				else if (ft_strchr2("|><", str[x][i], 3))
				{
					if ((x == 0) || (str[x] && str[x - 1] && ft_strchr2(" \t", str[x - 1][0], 2))
						|| (str[x] && str[x - 1] && ft_strchr2(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1], 2)))	
							s[index] = ft_strdup("1");//this for "|" pipe inside quote or ">" or "<"
					while (str[x][i] && str[x][i] != '"')
						i++;
					s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
				}
				else
				{
					i = star;
					while(str[x][i] && str[x][i] != '"')
						i++;
					if ((x == 0) || (x > 0 && str[x - 1][0] == '"' && str[x - 1][1] == '"' && !ft_strchr2(" \t", str[x][0], 2))
					|| (x > 0 && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && str[x][0] == '"'))
					{
						if (!s[index])
								s[index] = ft_calloc(1, 1);
						s[index] = ft_strjoin_new(s[index], str[x], star, i - 1); // this for first arg between ("asdasda")
					}
					else if ((str[x - 1][0] && ft_strchr2(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1], 2))) // this is for second string inside (space "asd") and before the string space that mean new strig have to allocted
						s[index] = ft_substr(str[x], star, i - 1);
					else if (x > 0 && str[x - 1])
						s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
				}
			}
			if (str[x][i] == '\'' && str[x][i + 1] != '\'')
			{
					i++;
				star = i;
				while (str[x][i] && !ft_strchr2("$|><'", str[x][i], 5))
					i++;
				if (str[x][i] == '$')
				{
					while (str[x][i] == '$')
						i++;
					while (str[x][i] && str[x][i] != '\'')
					{
						if (!s[index])
							s[index] = ft_calloc(1, 1);
						if (!ft_isalpha(str[x][i]))
						{
							s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
							s[index] = ft_strjoin_new(s[index], "4", 0, 0);
							star = i;
						}
						i++;
					}
					if (str[x][i] == '\'')
					{
						if (!s[index])
							s[index] = ft_calloc(1, 1);
						s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
					}
					s[index] = ft_strjoin_new(s[index], "4", 0, 0);
				}
				else if (ft_strchr2("|><", str[x][i], 3))
				{
					if ((x == 0) || (str[x] && str[x - 1] && ft_strchr2(" \t", str[x - 1][0], 2))
						|| (str[x] && str[x - 1] && ft_strchr2(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1], 2)))
							s[index] = ft_strdup("1");//this for '|' pipe inside quote or ">" or "<"
					while (str[x][i] && str[x][i] != '\'')
						i++;
					s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
				}
				else
				{
					i = star;
					while(str[x][i] && str[x][i] != '\'')
						i++;
					if ((x == 0) || (x > 0 && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && !ft_strchr2(" \t", str[x][0], 2))
						|| (x > 0 && str[x - 1][0] == '"' && str[x - 1][1] == '"' && str[x][0] == '\''))
						{
							if (!s[index])
									s[index] = ft_calloc(1, 1);
							s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
						}
					else if ((str[x - 1] && ft_strchr2(" \t", str[x - 1][ft_strlen(str[x - 1]) - 1], 2)))
						s[index] = ft_substr(str[x], star, i - star);
					else if (x > 0 && str[x - 1])
						s[index] = ft_strjoin_new(s[index], str[x], star, i - 1);
				}
			}
			x++;
			i = 0;
		}
		free2d(str);
	// (void)env;
	// (void)my_env;
	final_expand = expand(s, my_env, num_alloc);
	final_expand = clean_expand(final_expand);
	export(final_expand, my_env, env);
	final_addition(final_expand);
	// while(1);
	}
	// free2d(final_expand);
}

int	main(int ac, char **av, char **env)
{
	int i;
	char *input;

	i = 0;
	(void)av;
	i = 0;
	t_list *my_env = NULL;
	my_env = get_env(env);
	if (ac != 1)
		return (1);
	while (1)
	{
		input = readline("minishell ~$ ");
		add_history(input);
		parser_arg(input, env, my_env);
		free(input);
	}
	return (0);
}
