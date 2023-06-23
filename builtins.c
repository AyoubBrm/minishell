/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:01 by shmimi            #+#    #+#             */
/*   Updated: 2023/06/22 22:02:29 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_chars(char *word)
{
	int		i;
	char	*special_chars;
	char	**test;

	i = 0;
	special_chars = "\\ ( ) < > | * ; ` ~ ";
	test = ft_split_origin(special_chars, ' ');
	while (test[i])
	{
		if (ft_strncmp(word, test[i], ft_strlen(word)) == 0)
		{
			// printf("here %s\n", word);
			return (0);
		}
		i++;
	}
	return (1);
}

void	my_echo(char **cmd)
{
	int	i;
	int	j;
	int	count_words;
	int	last_word;
	int	n;

	i = 2; // avoid echo and -n
	j = 1;
	count_words = 0;
	last_word = 0;
	n = 0;
	if (!cmd[j])
	{
		printf("\n");
		return ;
	}
	else if (ft_strncmp(cmd[j], "-n", 2) == 0 && !cmd[j + 1])
	{
		return ;
	}
	while (cmd[i])
	{
		if (handle_special_chars(cmd[i]))
		{
			count_words++;
		}
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		if (handle_special_chars(cmd[i]) && ft_strncmp(cmd[i], "-n", 2) != 0)
		{
			printf("%s ", cmd[i]);
		}
		else if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			i++;
			n = i;
			while (handle_special_chars(cmd[n]))
			{
				last_word++;
				if (last_word == count_words)
				{
					printf("%s", cmd[n]);
					break ;
				}
				printf("%s ", cmd[n]);
				n++;
			}
			break ;
		}
		i++;
	}
	if (ft_strncmp(cmd[j], "-n", 2) != 0)
		printf("\n");
}

void	my_cd(char *path, t_list *my_env)
{
	t_list	*current;
	int		home_found;

	current = my_env;
	home_found = 0;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 4) == 0)
		{
			home_found = 1;
			break ;
		}
		current = current->next;
	}
	current = my_env;
	if (path)
	{
		if (chdir(path) != 0)
			printf("cd: %s: No such file or directory\n", path);
	}
	else if (!path && home_found)
	{
		while (current)
		{
			if (ft_strncmp(current->key, "HOME", 4) == 0)
			{
				chdir(current->value);
				break ;
			}
			current = current->next;
		}
	}
	else
		printf("cd: HOME not set\n");
}

char	*my_pwd(void)
{
	int		size;
	char	*buf;
	char	*pwd;

	size = 5;
	buf = malloc(size);
	while (getcwd(buf, size) == NULL)
	{
		size += size;
		buf = my_realloc(buf, size);
	}
	pwd = getcwd(buf, size);
	printf("%s\n", pwd);
	free(buf);
	return (pwd);
}

void	*my_realloc(char *ptr, int size)
{
	if (ptr == NULL)
		return (NULL);
	free(ptr);
	ptr = malloc(size);
	return (ptr);
}

void	free_env(void *env)
{
	(void)env;
	// t_list *env_var = (t_list *)env;
	// free2d(env_var->all);
	// free(env_var->key);
	// free(env_var->value);
	// free(env_var);
}

t_list	*get_env(char **env)
{
	int		i;
	t_list	*current;
	t_list	*new_env;
	t_list	*head;
	char	**env_old;

	i = 0;
	// int j = 0;
	// int lol = 0;
	current = NULL;
	new_env = NULL;
	head = NULL;
	env_old = NULL;
	// char *key = NULL;
	// char *value = NULL;
	while (env[i])
	{
		// free (key);
		// free2d (env_old);
		// free (value);
		// free_env(new_env);
		new_env = malloc(sizeof(t_list));
		env_old = ft_split_origin(env[i], '=');
		new_env->key = ft_strdup(env_old[0]);
		new_env->value = ft_strdup(env_old[1]);
		// free2d(env_old);
		// new_env->all = malloc(ft_strlen(key) + ft_strlen(value) + 1);
		// new_env->all = ft_strjoin(new_env->key, ft_strchr_inc(env[i], '='));
		new_env->next = NULL;
		if (current == NULL)
		{
			head = new_env;
			current = head;
		}
		else
		{
			current->next = new_env;
			current = current->next;
		}
		i++;
		// new_env = new_env->next;
		// if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
		// {
		//     freenode(&new_env, current);
		// }
	}
	// new_env->next = NULL;
	return (head);
}

void	new_env(t_list *my_env)
{
	t_list	*current;

	current = my_env;
	while (current != NULL)
	{
		// if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
		// {
		//     freenode(&my_env, current);
		// }
		if (ft_strncmp(current->key, "_", 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup("env");
			current->all = ft_strjoin(current->key, "=env");
			printf("%s\n", current->all);
		}
		else if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	myexport(char **cmd, t_list *my_env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	int		len;
	int		k;
	int		b;
	int		offset;
	int		equal;
	t_list	*new_export;
	t_list	*current;
	t_list	*my_export;
	int		lol;
	int		z;

	i = 1;
	j = 0;
	key = NULL;
	value = NULL;
	offset = 0;
	equal = 1;
	lol = 0;
	current = my_env;
	my_export = malloc(sizeof(t_list));
	if (!cmd[1])
	{
		while (current)
		{
			k = 2;
			b = 0;
			my_export->key = ft_strdup(current->key);
			if (current->value)
			{
				len = ft_strlen(current->value);
				my_export->value = malloc(len + 4);
				my_export->value[0] = '=';
				my_export->value[1] = '"';
				while (k < len + 2)
				{
					my_export->value[k] = current->value[b];
					k++;
					b++;
				}
				my_export->value[k] = '"';
				k++;
				my_export->value[k] = '\0';
				my_export->key_exp = ft_strjoin(ft_strdup("declare -x "),
					my_export->key);
				my_export->all = ft_strjoin(my_export->key_exp,
					my_export->value);
				my_export->next = NULL;
				printf("%s\n", my_export->all);
			}
			else
				printf("declare -x %s\n", my_export->key);
			current = current->next;
		}
	}
	current = my_env;
	z = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == '+' && cmd[i][j + 1] == '+')
			{
				printf("Minishell: export: `%s': not a valid identifier\n",
					cmd[i]);
				return ;
			}
			else if ((cmd[i][j] == '+' && cmd[i][j + 1] == '=')
				|| cmd[i][j] == '=')
			{
				if (!key)
					key = ft_substr(cmd[i], 0, j);
				value = ft_strchr_inc(cmd[i], '=');
				while (key[z])
				{
					if (!ft_isalpha(key[z]))
					{
						if (key[z] != '_')
						{
							printf("Minishell: export: `%s': not a valid identifier\n",
								cmd[i]);
							return ;
						}
					}
					z++;
				}
			}
			j++;
		}
		i++;
	}
	i = 1;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		equal = 1;
		current = my_env;
		while (cmd[i][j])
		{
			if ((cmd[i][j] == '=' || cmd[i][j] == '+') && equal)
			{
				offset = 1;
				equal = 0;
				key = ft_strdup(ft_substr(cmd[i], 0, j));
				value = ft_strdup(ft_strchr(cmd[i], '='));
				while (current)
				{
					if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
					{
						 if (!current->value) //!(ft_strncmp(current->value, value, -1) == 0)
						{
							if (!current->value)
							{
								// free(current->value);
								current->value = ft_strdup(ft_strchr(cmd[i],
										'='));
							}
							if (current->all)
								free(current->all);
							current->all = ft_strjoin(key,
								current->value);
							printf("%s\n", current->all);
						}
						else
						{
							free(current->value);
							current->value = ft_strdup(ft_strchr(cmd[i], '='));
							current->all = ft_strjoin(key, current->value);
						}
						lol = 1;
						break ;
					}
					current = current->next;
				}
				if (!lol)
				{
					new_export = malloc(sizeof(t_list));
					new_export->key = key;
					new_export->value = value;
					new_export->all = malloc(ft_strlen(key) + ft_strlen(value)
						+ 1);
					new_export->all = ft_strjoin(key, ft_strchr_inc(cmd[i],
							'='));
					new_export->next = NULL;
					ft_lstadd_back(&my_env, new_export);
				}
				lol = 0;
			}
			j++;
		}
		if (!offset)
		{
			current = my_env;
			while (current)
			{
				if (ft_compare(current->key, cmd[i]) == 0)
				{
					offset = 1;
				}
				else
				{
					printf("loool\n");
					offset = 0;
					break ;
				}
				current = current->next;
			}
			if (offset)
			{
				new_export = malloc(sizeof(t_list));
				new_export->key = ft_strdup(cmd[i]);
				new_export->value = NULL;
				new_export->all = NULL;
				new_export->next = NULL;
				ft_lstadd_back(&my_env, new_export);
				offset = 0;
			}
		}
		i++;
	}
}

void	my_unset(char **to_unset, t_list *my_env)
{
	t_list	*current;
	t_list	*tmp;
	int		i;

	i = 1;
	while (to_unset[i])
	{
		current = my_env;
		while (current)
		{
			if (ft_strncmp(current->key, to_unset[i],
					ft_strlen(to_unset[i])) == 0)
			{
				tmp = current->next;
				freenode(&my_env, current);
				current = tmp;
			}
			if (current)
				current = current->next;
		}
		i++;
	}
}

// void convert_env(t_list *env)
// {
//     t_list *current;
//     char **new_env;

//     current = env;

//     while(current)
//     {

//     }
// }

// void exit()
// {
//     int id = fork();

//     if (id == 0)
//     {
//         printf("exit\n");

//     }
// }