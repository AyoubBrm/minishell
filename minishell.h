/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:39 by shmimi            #+#    #+#             */
/*   Updated: 2023/05/31 01:38:16 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
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
int	account_quote(char *input);
char **clean_expand(char **final_expand);


#endif