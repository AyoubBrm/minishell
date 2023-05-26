/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/05/27 00:52:36 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char* find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand, int flags)
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
				return(temp_expand = ft_strjoin_new(temp_expand, env->value, 0, ft_strlen(env->value)));
		}
		env = env->next;
	}
	if(flags == 4)
		return(ft_strjoin(temp_expand, var));
	else if (var[0] == '$' && var[1] >= '0' && var[1] <= '9')
		return(ft_strjoin(temp_expand, &var[2]));
	else if(ft_strchr(var, '$') && ft_strlen(var) == 1)
		return(ft_strjoin(temp_expand, var));
	return(temp_expand);
}
void expand(char **s, t_list *my_env)
{
	int		i;
	int		x;
	int		star;
	char	*var;
	char	*temp_expand;
	temp_expand = ft_calloc(1,1);
	x = 0;
	while (s[x])
	{
		i = 0;
		while (s[x][i])
		{
			while (s[x][i] == '$' && s[x][i + 1] == '$')
				i++;
			if (s[x][i] == '$' && s[x][i + 1] != '@')
			{
				if ((ft_strchr(s[x] ,'\3') || !ft_strchr(s[x] ,'\3')))
				{
					star = i;
					i++;
					while ((ft_isdigit(s[x][i]) || ft_isalpha(s[x][i]) ||  s[x][i] == '_') && !ft_strchr("\3\4\5\6$", s[x][i]))
						i++;
					var = ft_substr(s[x], star, i - star);
					printf("%s\n", var);
					if(s[x][i] == '\4')
						temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 4);
					else if (s[x][i] == '"' && s[x][i + 1] == '\4')
						temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 4);
					else
						temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 0);
				}
				if (ft_strchr(s[x], '"'))
				{
					star = i;
					while (s[x][i] != '"' && s[x][i])
						i++;
					temp_expand = ft_strjoin_new(temp_expand, s[x], star, i - 1);
				}
			}
			else if (s[x][i] == '$' && s[x][i + 1] == '@' && !ft_strchr(&s[x][i], '\4'))
				i += 2;
			else if (s[x][i] == '$' && s[x][i + 1] == '@' && ft_strchr(&s[x][i], '\4'))
			{
				star = i;
				while (s[x][i] && s[x][i] != '\4')
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
		s[x] = ft_substr(temp_expand, 0, ft_strlen(temp_expand));
		temp_expand = ft_substr("", 0, 0);
		x++;
	}
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
	size_t x;
	size_t i = 0;
	char **str;
	char **s;
	int z = 0;
	int a = 0;
	int quote = 0;
	int		star = 0;
	// (void)env;
	// (void)my_env;
	str = ft_split(input, '\"');
	x = 0;
	while(input[x])
	{
		if (input[x] == '"')
		{
			x++;
			quote++;
			while (input[x] && input[x] != '"')
				x++;
			if (input[x] == '"')
				quote++;
		}
		if (input[x] == '\'')
		{
			x++;
			quote++;
			while (input[x] && input[x] != '\'')
				x++;
			if (input[x] == '\'')
				quote++;
		}
		x++;
	}
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
			if ((!ft_strchr2(" \"'><|", input[x], 6) && input[x + 1] == ' ')
				|| (!ft_strchr2(" \"'><|", input[x], 6) && input[x + 1] == '\0')
				|| (!ft_strchr2(" \"'><|", input[x], 6) && input[x + 1] == '"'))
				a++;
			while (!ft_strchr2(" \"'><|", input[x], 6) && input[x])
				x++;
		}
		if (input[x] == '>' || input[x] != '|' || input[x] != '<')
		{
			if((input[x] == '>' && input[x + 1] == '>') || (input[x] == '<' && input[x + 1] == '<'))
				x += 2;
			if (input[x] == '>' && input[x + 1])
				a++;
			a++;
		}
		if (input[x] == '"')
		{
			if (input[x] == '"' && input[x])
				x++;
			while (input[x] != '"' && input[x])
				x++;
			if (input[x] == '"' )
			{
				a++;
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
				a++;
				x++;
			}	
		}
		x++;
	}
	s = ft_calloc(sizeof(char *) , a + 2);
	if (quote % 2 == 1)
			printf("%s\n", "minishell: syntax error near unexpected token `\"' or `\''");
	else if (ft_strchr2("><|", input[0], 3) && ft_strlen(input) == 1)
		printf("minishell: syntax error near unexpected token `%c'\n", input[0]);
	else if ((input[0] == '|' && input[1] == '|' && ft_strlen(input) == 2) 
			|| (input[0] == '<' && input[1] == '<' && ft_strlen(input) == 2)
			|| (input[0] == '>' && input[1] == '>' && ft_strlen(input) == 2))
		printf("minishell: syntax error near unexpected token `%c%c'\n", input[0],input[0]);
	else
	{
		x = 0;
		while (str[x])
		{
			if (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
			{
				while (str[x][i] == ' ')
					i++;
				if (i > 0 && x > 0 && str[x][i - 1] == ' ')
					z++;
				if (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
				{
					star = i;
					while (str[x][i] && !ft_strchr2("\'\"", str[x][i], 2))
					{	
						if ((str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '"')
							|| (str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '\''))
						{
							if (!s[z])
								s[z] = ft_calloc(1, 1);
							s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
							x++;
							i = 0;
							star = 0;
							while(str[x][i] && !ft_strchr2("\'\" ", str[x][i], 3))
								i++;
							s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
						}
						else
						{
							if (!s[z])
								s[z] = ft_calloc(1, 1);
							while(str[x][i] && !ft_strchr2("\'\" $><|", str[x][i], 7))
								i++;
							if ((str[x] && str[x][i] == '$' && str[x][i + 1]) || (str[x] && str[x][i] == '$' && str[x][i + 1] == '\0' && !str[x + 1]))
							{
								i++;
								while ((str[x][i] && !ft_strchr2(" $><|", str[x][i], 5)))
									i++;
								s[z] = ft_strjoin_new(s[z], str[x],star, i - 1);
								if (str[x][i] && str[x][i] == '$' && str[x][i - 1])
									s[z] = ft_strjoin_new(s[z], "\5", 0, 0);
								else if ((str[x][i] && str[x][i] != ' ' && str[x + 1][0] && str[x + 1][0] == '"' && str[x + 1][1] == '"')
									|| (str[x][i] && str[x][i] != ' ' &&  str[x - 1][0] && str[x - 1][0] == '"' && str[x - 1][1] == '"')
									|| (str[x][i] && str[x][i] != ' ' && str[x + 1][0] && str[x + 1][0] == '\'' && str[x + 1][1] == '\'')
									|| (str[x][i] && str[x][i] != ' ' && str[x - 1][0] && str[x - 1][0] == '\'' && str[x - 1][1] == '\''))
										s[z] = ft_strjoin_new(s[z], "\5", 0, 0);
								else
									s[z] = ft_strjoin_new(s[z], "\6", 0, 0);
							}
							else
								s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
							if (str[x][i] == ' ')
								z++;
							while (str[x][i] == ' ')
								i++;	
							if (str[x][i] && ft_strchr2("<>|", str[x][i], 3))
							{
								if ((i > 0 && str[x][i - 1] && str[x][i - 1] != ' ')
									|| (i > 0 && !ft_strchr2(&str[x][0], ' ', i)) || (x > 0 && i == 0))
									z++;
								star = i;
								if (!s[z])
									s[z] = ft_calloc(1, 1);
								while (str[x][i] && ft_strchr2("<>|", str[x][i], 3))
										i++;
									s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
								if (str[x][i] != ' ' && str[x][i])
									z++;
								else if ((!ft_strchr2(&str[x][i], ' ', ft_strlen(str[x]) - i) && str[x + 1]))
									z++;
								if (!s[z])
									s[z] = ft_calloc(1, 1);
							}
							star = i;
						}
					}
				}
			}
			if ((str[x] && x > 0 && str[x][i] && str[x][0] == '"'  && str[x][1] == '"' && str[x + 1]// when string -1 and string +1 : is exist this code for this arg (ss "" ss "" ss) before string space and after it and inside string '0' this for "" qoute index most be > 0
				&& str[x + 1][0] == ' ' && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
				|| (str[x] && x > 0 && str[x][i] && str[x][0] == '\'' && str[x][1] == '\''// when string -1 and string +1 : is exist this code for this arg (ss '' ss '' ss) before string space and after it and inside string '\0' this for '' qoute index most be > 0
				&& str[x + 1] && str[x + 1][0] == ' ' && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
				|| (x > 0 && str[x] && str[x][0] == '"' && str[x][1] == '"' && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ' ) // when string -1 and string +1 : is exist this code for this arg (ss '' ss '' ss) before string space and after it and inside string '\0' this for '' qoute index most be > 0
				|| (x > 0 && str[x] && str[x][0] == '\'' && str[x][1] == '\'' && str[x - 1]  && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ' ))
			{
				if (!s[z])
					s[z] = ft_calloc(2, 1);
			}
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
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
					}
					s[z] = ft_strjoin_new(s[z], "\3", 0, 0);
				}
				else if (ft_strchr("<>|", 3))
				{
					if ((x == 0 ) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
						|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
						|| (str[x] && str[x + 1] && str[x + 1][0] == ' '))
							s[z] = ft_strdup("\1");//this for "|" pipe inside quote or ">" or "<"
					while (str[x][i] && str[x][i] != '"')
						i++;
					s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
				}
				else
				{
					i = star;
					while(str[x][i] && str[x][i] != '"')
						i++;
					if ((x == 0) || (x > 0 && str[x - 1] && str[x - 1][0] == '"' && str[x - 1][1] == '"' && str[x][0] != ' ')
					|| (x > 0 && str[x - 1] && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && str[x][0] == '"'))
					{
						if (!s[z])
								s[z] = ft_calloc(1, 1);
						s[z] = ft_strjoin_new(s[z], str[x], star, i - 1); // this for first arg between ("asdasda")
					}
					else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')) // this is for second string inside (space "asd") and before the string space that mean new strig have to allocted
						s[z] = ft_substr(str[x], star, i - 1);
					else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
						s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
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
						i++;
					if (str[x][i] == '\'')
					{
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
					}
					s[z] = ft_strjoin_new(s[z], "\4", 0, 0);
				}
				else if (ft_strchr2("|><", str[x][i], 3))
				{
					if ((x == 0) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
						|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
							s[z] = ft_strdup("\1");//this for '|' pipe inside quote or ">" or "<"
					while (str[x][i] && str[x][i] != '\'')
						i++;
					s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
				}
				else
				{
					i = star;
					while(str[x][i] && str[x][i] != '\'')
						i++;
					if ((x == 0) || (x > 0 && str[x - 1] && str[x - 1][0] == '\'' && str[x - 1][1] == '\'' && str[x][0] != ' ')
						|| (x > 0 && str[x - 1] && str[x - 1][0] == '"' && str[x - 1][1] == '"' && str[x][0] == '\''))
						{
							if (!s[z])
									s[z] = ft_calloc(1, 1);
							s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
						}
					else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
						s[z] = ft_substr(str[x], star, i - star);
					else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
						s[z] = ft_strjoin_new(s[z], str[x], star, i - 1);
				}
			}
			x++;
			a = 0;
			i = 0;
		}
	}
	(void)env;
	// (void)my_env;
	expand(s, my_env);
	// export(s, my_env, env);
	// printf("******************************\n");	
	// i = 0;
	// while (str[i])
	// 	printf("------*str----*%s\n", str[i++]);
	// printf("******************************\n");	
	i = 0;
	while (s[i])
		printf("----*s----*%s\n", s[i++]);
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

	}
	return (0);
}
