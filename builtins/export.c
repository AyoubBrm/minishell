/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:26:01 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/23 19:31:30 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_myexport(char *cmd, int i)
{
    if ((cmd[i] >= 32 && cmd[i] <= 47) || (cmd[i] >= 58 && cmd[i] <= 60) || (cmd[i] >= 63 && cmd[i] <= 64) || (cmd[i] >= 91 && cmd[i] <= 94) || (cmd[i] >= 123 && cmd[i] <= 126) || cmd[i] == 96)
    {
        return (1);
    }
    return (0);
}

int get_equal_pos(char *key)
{
    int i;

    i = 0;
    while (key[i])
    {
        if (key[i] == '=')
            return (i + 1);
        i++;
    }
    return (ft_strlen(key));
}

void my_export_alloc(t_list **my_export, t_list *current, int b, int k)
{
    (*my_export)->value = malloc(ft_strlen(current->value) + 4);
    (*my_export)->value[0] = '=';
    (*my_export)->value[1] = '"';
    while (k < ft_strlen(current->value) + 2)
    {
        (*my_export)->value[k] = current->value[b];
        k++;
        b++;
    }
    (*my_export)->value[k] = '"';
    k++;
    (*my_export)->value[k] = '\0';
    (*my_export)->key_exp = ft_strjoin_no_free("declare -x ",
                                               (*my_export)->key);
    (*my_export)->all = ft_strjoin_no_free((*my_export)->key_exp,
                                           (*my_export)->value);
    (*my_export)->next = NULL;
    printf("%s\n", (*my_export)->all);
}

int my_export_check2(char **cmd, t_pipes_n_redirection *pipes_n_redirection)
{
    int i = 0;
    int j = 0;
    char *key;
    while (cmd[i])
    {
        key = ft_substr(cmd[i], 0, get_equal_pos(cmd[i]));
        while (key[j] && key)
        {
            if (check_myexport(key, j))
            {
                ft_printf("bash: not a valid identifiers\n");
                global_struct.g_exit_status = 1;
                pipes_n_redirection->exit_builtin = 1;
                return 1;
            }
            j++;
        }
        j = 0;
        i++;
        free(key);
    }
    return 0;
}

void myexport(char **cmd, t_list *my_env,
              t_pipes_n_redirection *pipes_n_redirection)
{
    int i;
    int j;
    char *key;
    char *value;
    char *tmp_key;
    int k;
    int b;
    int offset;
    int equal;
    int flag;
    // t_list *new_export;
    t_list *current;
    t_list *my_export;
    int lol;
    int z;

    i = 0;
    j = 0;
    key = NULL;
    value = NULL;
    tmp_key = NULL;
    offset = 0;
    equal = 1;
    flag = 0;
    lol = 0;
    current = my_env;
    my_export = malloc(sizeof(t_list));
    if (!cmd[0])
    {
        while (current)
        {
            k = 2;
            b = 0;
            my_export->key = ft_strdup(current->key);
            if (current->value)
                my_export_alloc(&my_export, current, b, k);
            else
                printf("declare -x %s\n", my_export->key);
            current = current->next;
        }
    }
    free(my_export);
    current = my_env;
    z = 0;
    
    if (my_export_check2(cmd, pipes_n_redirection))
        return ;
    
    key = NULL;
    i = 0;
    j = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (ft_isdigit(cmd[i][0]) || !ft_isalpha(cmd[i][0]))
            {
                if (cmd[i][0] == '_')
                    break;
                ft_printf("bash: not a valid identifierss\n");
                global_struct.g_exit_status = 1;
                pipes_n_redirection->exit_builtin = 1;
                flag = 1;
                break;
            }
            if ((cmd[i][j] == '+' && cmd[i][j + 1] == '+'))
            {
                ft_printf("bash: not a valid identifier\n");
                global_struct.g_exit_status = 1;
                pipes_n_redirection->exit_builtin = 1;
                flag = 1;
                break;
            }
            else if ((cmd[i][j] == '+' && cmd[i][j + 1] == '=') || cmd[i][j] == '=' || cmd[i][j] == '+')
            {
                if (!key)
                    key = ft_substr(cmd[i], 0, j);
                value = ft_strchr_inc(cmd[i], '=');
                while (key[z])
                {
                    if (!ft_isalpha(key[z]))
                    {
                        if (key[z] != '_' && (!ft_isdigit(key[z])))
                        {
                            ft_printf("bash: not a valid identifier\n");
                            free(key);
                            key = NULL;
                            global_struct.g_exit_status = 1;
                            pipes_n_redirection->exit_builtin = 1;
                            flag = 1;
                            break;
                        }
                        flag = 0;
                    }
                    z++;
                }
            }
            j++;
        }
        if (!flag)
            my_export_add(cmd[i], my_env);
        flag = 0;
        i++;
    }
    if (key)
        free(key);
    i = 0;
    j = 0;
    if (!pipes_n_redirection->exit_builtin)
        pipes_n_redirection->exit_builtin = 0;
    // while(1);
}

void my_export_add(char *cmd, t_list *my_env)
{
    int equal;
    int offset = 0;
    char *key = NULL;
    char *value = NULL;
    char *tmp_key = NULL;
    int j = 0;
    int lol = 0;
    t_list *current;
    t_list *new_export;

    j = 0;
    equal = 1;
    current = my_env;

    while (cmd[j])
    {
        if ((cmd[j] == '=' || cmd[j] == '+') && equal)
        {
            offset = 1;
            equal = 0;
            free(key);
            free(value);
            tmp_key = ft_substr(cmd, 0, j);
            key = ft_strdup(tmp_key);
            free(tmp_key);
            value = ft_strdup(ft_strchr(cmd, '='));
            while (current)
            {
                if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
                {
                    if (!current->value)
                    {
                        free(value);
                        value = ft_strchr(cmd, '=');
                        current->value = ft_strdup(value);
                        current->all = ft_strjoin_no_free(key, current->value);
                        free(key);
                    }
                    else
                    {
                        free(current->all);
                        free(current->value);
                        free(value);
                        value = ft_strchr(cmd, '=');
                        current->value = ft_strdup(value);
                        current->all = ft_strjoin_no_free(key, current->value);
                        free(key);
                    }
                    lol = 1;
                    break;
                }
                current = current->next;
            }
            if (!lol)
            {
                new_export = malloc(sizeof(t_list));
                new_export->key = ft_strdup(key);
                new_export->value = ft_strdup(value);
                new_export->all = ft_strjoin_no_free(key, ft_strchr_inc(cmd,
                                                                        '='));
                free(key);
                free(value);
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
            if (ft_strncmp(current->key, cmd, ft_strlen(cmd)) == 0)
            {
                offset = 1;
                break;
            }
            offset = 0;
            current = current->next;
        }
        if (!offset)
        {
            new_export = malloc(sizeof(t_list));
            new_export->key = ft_strdup(cmd);
            new_export->value = NULL;
            new_export->all = NULL;
            new_export->next = NULL;
            ft_lstadd_back(&my_env, new_export);
            offset = 0;
        }
    }
}