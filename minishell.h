/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/06/18 15:55:40 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <signal.h>
#include <sys/errno.h>

typedef struct s_myenv
{
    char *key;
    char *value;
    struct s_myenv *next;
}   t_myenv;

typedef struct s_env
{
    char *pwd;
    // char **myenv;
}   t_env;

void *my_realloc(char *ptr, int size);
//Built-ins
void    my_echo(char **cmd);
void    my_cd(char *path, t_list *myenv);
char    *my_pwd();
void    my_env(char **env, char **cmd, t_env *myenv);
t_list  *get_env(char **env);
void    new_env(t_list *head);
void    exit();
void    myexport(char **cmd, t_list *my_env);

void    my_unset(char **to_unset, t_list *my_env);

//Free
void	free2d(char **arg);
void    free_env(void *env);
void    freenode(t_list **lst, t_list *node);

//barssing

typedef struct s_addition
{
	int how_many;
	char **type;
	char **file;
	char *pipe;
	
}t_redirection;

typedef struct s_tab
{
	int pip;
	char *cmd;
	t_redirection *redirection;
	char **arg;
	struct s_tab *next;
	int		ambiguous;
	int		no_file_dire;
}t_table;

typedef struct s_my
{
	int x;
	int i;
	int index;
}t_myarg;

int	account_quote(char *input);
char **clean_expand(char **final_expand);
void free_list(t_table *head);
void free_list(t_table *head);
t_table *error(t_table *list);
void ambiguous_no_file(t_table *head);
int num_alloc_str(char *input);


#endif