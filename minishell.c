/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:20 by abouram           #+#    #+#             */
/*   Updated: 2023/05/22 00:53:37 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char* find_in_env_and_alloced(t_list *my_env, char *var, char *temp_expand, int flags)
{
	int x;
	x = 0;
	int i;
	i = 0;
	t_list *env;
	env = my_env;
	while(env != NULL)
	{
		if (ft_strncmp(&var[1], env->key,  ft_strlen(var) + 1) == 0)
		{
			if(flags == 4)
				return(var);
			else
				temp_expand = ft_strjoin_new(temp_expand, env->value, ft_strlen(temp_expand) - 1, 0, ft_strlen(env->value) -1);
		}
		env = env->next;
	}
	if(flags == 4)
		return(ft_strdup("4"));
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
			if (s[x][i] == '$')
			{
				star = i;
				i++;
				while ((ft_isdigit(s[x][i]) || ft_isalpha(s[x][i]) ||  s[x][i] == '_' ) && s[x][i] != '3' && s[x][i] != '4' && s[x][i] != '2')
					i++;
				var = ft_substr(s[x], star, i - star);
				if (s[x][i] == '4')
					temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 4);
				else
					temp_expand = find_in_env_and_alloced(my_env, var, temp_expand, 2);
			}
			else
			{
				star = i;
				while ((s[x][i] && s[x][i] != '$') || (s[x][i] && s[x][i] != '4' && s[x][i - 1]))
					i++;
				temp_expand = ft_strjoin_new(temp_expand, s[x], ft_strlen(temp_expand), star, i - 1);
			}
			i++;
		}
		s[x] = ft_substr(temp_expand, 0, ft_strlen(temp_expand ));
		temp_expand = ft_substr("", 0, 0);
		printf("%s\n", s[x]);
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
		if (quote % 2 == 1)
		{
			printf("%s\n", "minishell: syntax error near unexpected token `\"' or `\''");
			exit(1);
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
			while (input[x] != ' ' && input[x] != '"' && input[x] != '\'' && input[x] != '>' && input[x] != '|' && input[x] != '<'
				&& input[x + 1] != ' ' && input[x + 1] != '"' && input[x + 1] != '\'' && input[x])
					x++;
			if ((input[x] != '|' && input[x] != '<' && input[x] != '>' && input[x] != '"' && input[x] != ' ' && input[x] != '\'' && input[x + 1] == ' ')
				|| (input[x] != '|' && input[x] != '<' && input[x] != '>' && input[x] != '"' && input[x] != '\'' && input[x] != ' ' && input[x + 1] == '\0')
				|| (input[x] != '|' && input[x] != '<' && input[x] != '>' && input[x] != '"' && input[x] != '\'' && input[x] != ' ' && input[x + 1] == '"'))
				a++;
			while (input[x] != '|' && input[x] != '<' && input[x] != '>' && input[x] != ' ' && input[x] != '"' && input[x] != '\'' && input[x])
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
	a = 0;
	x = 0;
	while (str[x])
	{
		if (str[x][i] && str[x][i] != '"' && str[x][i] != '\'')
		{
			while (str[x][i] == ' ')
				i++;
			if ((str[x][0] == ' ' && x > 0 && str[x][i] != '>')
				|| (((str[x][i] == '>' || str[x][i] == '|' || str[x][i] == '<') && i > 0))) 
				z++;
			if (str[x][i] && str[x][i] != '"' && str[x][i] != '\'')
			{
				star = i;
				while (str[x][i] && str[x][i] != '"' && str[x][i] != '\'')
				{	
					if ((str[x] && str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '"')
						|| (str[x] && str[x + 1] && str[x][i] == '$' && str[x][i + 1] == '\0' && str[x + 1][0] == '\''))
					{
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						x++;
						i = 0;
						star = 0;
						while(str[x][i] && str[x][i] != '\'' && str[x][i] != '"' && str[x][i] != ' ')
							i++;
						s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
					}
					else
					{
						if (!s[z])
							s[z] = ft_calloc(1, 1);
						while(str[x][i] && str[x][i] != '"' && str[x][i] != '\'' && str[x][i] != ' ' && str[x][i] != '$' && str[x][i] != '>' && str[x][i] != '|' && str[x][i] != '<')
							i++;
						if ((str[x] && str[x][i] == '$' && str[x][i + 1]) || (str[x] && str[x][i] == '$' && str[x][i + 1] == '\0' && !str[x + 1]))
						{
							i++;
							while (str[x][i] && str[x][i] != '$' && str[x][i] != ' ' && str[x][i] != '>')
								i++;
							s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]),star, i - 1);
							if (str[x + 1] && str[x][i] != '$' && str[x][i] != ' ' && str[x + 1][0] == '"' && str[x + 1][1] != '"')
								s[z] = ft_strjoin_new(s[z], "2", ft_strlen(s[z]), 0, 0);
							else if ((str[x][i] && str[x][i] != '$' && str[x][i] != ' ' && str[x - 1][i] && str[x - 1][0] == '"' && str[x - 1][1] == '"')
							|| (str[x][i] && str[x][i] != '$' && str[x][i] != ' ' && str[x + 1][i] && str[x + 1][0] == '"' && str[x + 1][1] == '"'))
								s[z] = ft_strjoin_new(s[z], "3", ft_strlen(s[z]), 0, 1);
						}
						else
							s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
						if (str[x][i] == ' ')
							z++;
						while (str[x][i] == ' ')
							i++;
						if ((str[x][i] && str[x][i] == '>') || (str[x][i] && str[x][i] == '|')
							|| (str[x][i] && str[x][i] == '<'))
						{
							star = i;
							if ((i > 0 && str[x][i - 1] != ' ' && str[x][i - 1]) || (!ft_strchr(str[x], ' ') && str[x - 1]))
								z++;
							if (!s[z])
								s[z] = ft_calloc(1, 1);
							while ((str[x][i] && str[x][i] == '>') || (str[x][i] && str[x][i] == '|')
								|| (str[x][i] && str[x][i] == '<'))
									i++;
								s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
							if ((str[x][i] != ' ' && str[x][i] && str[x][i + 1] != '>') || (str[x][ft_strlen(str[x]) - 1] != ' ' && str[x + 1] && str[x + 1][0]))
								z++;
							if (!s[z])
								s[z] = ft_calloc(1, 1);
						}
						star = i;
					}
				}
			}
		}
		if ((str[x] && x > 0 && str[x][i] && str[x][0] == '"'  && str[x][1] == '"' && str[x + 1]// when string -1 and string +1 : is exist this code for this arg (ss "" ss "" ss) before string space and after it and inside string '\0' this for "" qoute index most be > 0
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
			while (str[x][i] && str[x][i] != '"' && str[x][i] != '>' && str[x][i] != '|' && str[x][i] != '<' && str[x][i] != '$')
				i++;
			if (str[x][i] == '$')
			{
				while (str[x][i] == '$')
					i++;
				while (str[x][i] && str[x][i] != '$' && str[x][i] != '"')
					i++;
				if (str[x][i] == '"')
				{
					if (!s[z])
						s[z] = ft_calloc(1, 1);
					s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
				}
				s[z] = ft_strjoin_new(s[z], "3", ft_strlen(s[z]), 0, 0);
			}
			else if (str[x][i] == '>' || str[x][i] == '|' || str[x][i] == '<')
			{
				if ((x == 0 ) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
					|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')
					|| (str[x] && str[x + 1] && str[x + 1][0] == ' '))
						s[z] = ft_strdup("1");//this for "|" pipe inside quote or ">" or "<"
				while (str[x][i] && str[x][i] != '"')
					i++;
				s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
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
					s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1); // this for first arg between ("asdasda")
				}
				else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' ')) // this is for second string inside (space "asd") and before the string space that mean new strig have to allocted
					s[z] = ft_substr(str[x], star, i - 1);
				else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
					s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
			}
		}
		if (str[x][i] == '\'' && str[x][i + 1] != '\'')
		{
				i++;
			star = i;
			while (str[x][i] && str[x][i] != '\'' && str[x][i] != '>' && str[x][i] != '|' && str[x][i] != '<' && str[x][i] != '$')
				i++;
			if (str[x][i] == '$' && str[x][i - 1] != '"')
			{
				while (str[x][i] == '$')
					i++;
				while (str[x][i] && str[x][i] != '$' && str[x][i] != '\'')
					i++;
				if (str[x][i] == '\'')
				{
					if (!s[z])
						s[z] = ft_calloc(1, 1);
					s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
				}
				s[z] = ft_strjoin_new(s[z], "4", ft_strlen(s[z]), 0, 0);
			}
			else if (str[x][i] == '>' || str[x][i] == '|' || str[x][i] == '<')
			{
				if ((x == 0) || (str[x] && str[x - 1] && str[x - 1][0] == ' ')
					|| (str[x] && str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
						s[z] = ft_strdup("1");//this for '|' pipe inside quote or ">" or "<"
				while (str[x][i] && str[x][i] != '\'')
					i++;
				s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
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
						s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
					}
				else if ((str[x - 1] && str[x - 1][ft_strlen(str[x - 1]) - 1] == ' '))
					s[z] = ft_substr(str[x], star, i - star);
				else if (str[x - 1] && str[x][ft_strlen(str[x]) - 1] != ' ')
					s[z] = ft_strjoin_new(s[z], str[x], ft_strlen(s[z]), star, i - 1);
			}
		}
		x++;
		a = 0;
		i = 0;
	}
	export(s, my_env, env);
	expand(s, my_env);
	// printf("******************************\n");	
	i = 0;
	// while (str[i])
	// 	printf("------*str----*%s\n", str[i++]);
	// printf("******************************\n");	
	// i = 0;
	// while (s[i])
	// 	printf("----*s----*%s\n", s[i++]);
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
