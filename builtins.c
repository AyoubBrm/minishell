/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:01 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/22 17:10:08 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_last_args(char **args)
{
    int i = 0;

    while (args[i])
    {
        if (ft_strncmp(args[i], "-n", 2) != 0)
            return i;
        i++;
    }
    return i - 1;
}
int handle_n(char *args)
{
    int i = 1;

    while (args[i])
    {
        if (args[i] != 'n')
            return 1;
        i++;
    }
    return 0;
}

void my_echo(char **cmd)
{

    int i;
    int flag = 0;
    int lol = 0;
    int blank = 0;
    int j = 2;
    int n = 0;
    i = 0;

    while (cmd[i])
    {
        if (ft_strncmp(cmd[i], "-n", 2) == 0 && !n)
        {
            if (!handle_n(cmd[i]) && !cmd[1])
                return;
            if (handle_n(cmd[i]))
            {
                flag = 1;
                while (cmd[i])
                {
                    if (!cmd[i + 1])
                        printf("%s", cmd[i]);
                    else
                        printf("%s ", cmd[i]);
                    i++;
                }
                break;
            }
            if (!handle_n(cmd[i]))
                blank = 1;
        }
        else
        {
            n = 1;
            flag = 1;
            if (!cmd[i + 1])
                printf("%s", cmd[i]);
            else
                printf("%s ", cmd[i]);
        }
        i++;
    }
    if (flag && !blank)
    {
        printf("\n");
        return ;
    }
    if (!flag && cmd[0])
    {
        lol = get_last_args(cmd);
        while (cmd[lol] && !(ft_strncmp(cmd[i - 1], "-n", 2) == 0)) // cmd[i - 1][0] != '-' && cmd[i - 1][1] != 'n'
        {
            if (!cmd[lol + 1])
                printf("%s", cmd[lol]);
            else
                printf("%s ", cmd[lol]);
            lol++;
        }
    }
    if (!blank)
        printf("\n");
}

int my_cd(char *path, t_list *my_env, t_pipes_n_redirection *pipes_n_redirection)
{
    t_list *current = my_env;
    int home_found = 0;
    pipes_n_redirection->exit_builtin = 1;
    while (current)
    {
        if (ft_strncmp(current->key, "HOME", 4) == 0)
        {
            home_found = 1;
            break;
        }
        current = current->next;
    }
    current = my_env;
    if (path)
    {
        if (chdir(path) != 0)
        {
            ft_printf("bash: cd: %s: No such file or directory\n", path);
            global_struct.g_exit_status = 1;
            return global_struct.g_exit_status;
        }
    }
    else if (!path && home_found)
    {
        while (current)
        {
            if (ft_strncmp(current->key, "HOME", 4) == 0)
            {
                chdir(current->value);
                break;
            }
            current = current->next;
        }
    }
    else
    {
        ft_printf("bash: cd: HOME not set\n");
     	global_struct.g_exit_status = 1;
        return global_struct.g_exit_status;
    }
    return global_struct.g_exit_status;
}

void my_pwd(t_list *my_env)
{
    char pwd[PATH_MAX];
    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
       global_struct.g_exit_status = 1;
        return;
    }
    printf("%s\n", pwd);
}

void *my_realloc(char *ptr, int size)
{
    if (ptr == NULL)
        return NULL;
    free(ptr);
    ptr = malloc(size);
    if (ptr == NULL)
        return NULL;
    return ptr;
}

t_list *get_env(char **env)
{
    int i = 0;

    t_list *current = NULL;
    t_list *new_env = NULL;
    t_list *head = NULL;

    char **env_old = NULL;

    while (env[i])
    {
        env_old = ft_split_origin(env[i], '=');
        new_env = ft_calloc(sizeof(t_list), 1);

        new_env->key = NULL;
        new_env->value = NULL;
        new_env->all = NULL;

        new_env->key = ft_strdup(env_old[0]);
        new_env->value = ft_strdup(env_old[1]);
        free2d(env_old);
        new_env->all = ft_strjoin_no_free(new_env->key, ft_strchr_inc(env[i], '='));
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
    }
    return head;
}

void new_env(t_list **my_env)
{
    t_list *current = *my_env;
    while (current)
    {
        if (current->key && current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void myexport(char **cmd, t_list *my_env, t_pipes_n_redirection *pipes_n_redirection)
{
    int i = 0;
    int j = 0;
    char *key = NULL;
    char *value = NULL;
    char *tmp_key = NULL;
    int len;
    int k;
    int b;
    int offset = 0;
    int equal = 1;
    int flag = 0;
    t_list *new_export;
    t_list *current;
    t_list *my_export;

    int lol = 0;
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
                my_export->key_exp = ft_strjoin_no_free("declare -x ", my_export->key);
                my_export->all = ft_strjoin_no_free(my_export->key_exp, my_export->value);
                my_export->next = NULL;
                printf("%s\n", my_export->all);
            }
            else
                printf("declare -x %s\n", my_export->key);
            current = current->next;
            // free(my_export->key_exp);
            // free(my_export->all);
            // free(my_export->key);
            // free(my_export->value);
        }
    }
    free(my_export);

    current = my_env;
    int z = 0;

    while (cmd[i])
    {
        // printf("%s\n", cmd[i]);
        j = 0;
        while (cmd[i][j])
        {
            if (ft_isdigit(cmd[i][0]))
            {
                ft_printf("bash: not a valid identifier\n");
                global_struct.g_exit_status = 1;
                pipes_n_redirection->exit_builtin = 1;
                flag = 1;
                break;
            }
            if (cmd[i][j] == '+' && cmd[i][j + 1] == '+')
            {
                ft_printf("bash: not a valid identifier\n");
                global_struct.g_exit_status = 1;
                pipes_n_redirection->exit_builtin = 1;
                flag = 1;
                break;
            }
            else if ((cmd[i][j] == '+' && cmd[i][j + 1] == '=') || cmd[i][j] == '=')
            {
                if (!key)
                    key = ft_substr(cmd[i], 0, j);
                value = ft_strchr_inc(cmd[i], '=');
                // printf("%s=%s\n", key, value);
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
            my_export_add(cmd[i], pipes_n_redirection, my_env, i);
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

void my_export_add(char *cmd, t_pipes_n_redirection *pipes_n_redirection, t_list *my_env, int i)
{
    int equal;
    int offset = 0;
    char *key;
    char *tmp_key;
    char *value;
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
            tmp_key = ft_substr(cmd, 0, j);
            key = ft_strdup(tmp_key);
            value = ft_strdup(ft_strchr(cmd, '='));
            while (current)
            {
                if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
                {
                    if (!current->value) //!(ft_strncmp(current->value, value, -1) == 0)
                    {
                        if (!current->value)
                        {
                            // free(current->value);
                            current->value = ft_strdup(ft_strchr(cmd, '='));
                            // printf("%p\n", current->value);
                        }
                        if (current->all)
                        {
                            // free(current->key);
                            // free(current->value);
                            // free(current->all);
                        }
                        current->all = ft_strjoin_no_free(key, current->value);
                        // printf("%s\n", current->all);
                    }
                    else
                    {
                        // free(current->value);
                        current->value = ft_strdup(ft_strchr(cmd, '='));
                        current->all = ft_strjoin_no_free(key, current->value);
                    }

                    lol = 1;
                    break;
                }
                current = current->next;
            }
            if (!lol)
            {
                new_export = malloc(sizeof(t_list));
                new_export->key = key;
                new_export->value = value;
                // new_export->all = malloc(ft_strlen(key) + ft_strlen(value) + 1);
                new_export->all = ft_strjoin_no_free(key, ft_strchr_inc(cmd, '='));
                new_export->next = NULL;
                // printf("key %s\n", new_export->key);
                // printf("key %s\n", new_export->key);
                // if (!(ft_strncmp(new_export->key, key, ft_strlen(key) + 1) == 0))
                // printf("??\n");
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
            if (ft_compare(current->key, cmd) == 0)
            {
                offset = 1;
            }
            else
            {
                offset = 0;
                break;
            }
            current = current->next;
        }
        if (offset)
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
    i++;
}

void my_unset(char **to_unset, t_list **my_env)
{
    t_list *current;
    t_list *tmp;

    int i = 0;

    current = *my_env;
    while (to_unset[i])
    {
        while (current)
        {
            if (current->next && current->key && ft_strncmp(current->key, to_unset[i], ft_strlen(to_unset[i]) + 1) == 0)
            {
                tmp = current->next;
                freenode(my_env, current);
                current = tmp;
            }
            else if (!current->next)
            {
                freenode(my_env, current);
                break;
            }
            current = current->next;
        }
        current = *my_env;
        i++;
    }
}

int my_exit(char **args, t_pipes_n_redirection *pipes_n_redirection)
{
    int i = 0;
    int j = 1;
    int overflow = 0;
    pipes_n_redirection->exit_builtin = 1;

    j = 0;

    while (args[i])
    {
        while (args[i][j])
        {
            if (!ft_isdigit(args[i][j]))
            {
                // printf("exit\n");
                if (args[i][0] == '-')
                {
                    j++;
                    while (ft_isdigit(args[i][j]) && !ft_isdigit(args[i][j]))
                        j++;
                    if (!ft_isdigit(args[i][j]) && args[i][j])
                    {
                        ft_printf("minishell: exit: %s: numeric argument required\n", args[i]);
                        exit(255);
                    }
                }
                j = 1;
                while (args[i][0] == '-' && ft_isdigit(args[i][j]))
                {
                    j++;
                    if (args[i][j] == '\0')
                        exit(255);
                }
                ft_printf("minishell: exit: %s: numeric argument required\n", args[i]);
                exit(255);
            }
            j++;
        }
        i++;
        j = 0;
    }

    if (args[0] && args[1])
    {
        // printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        global_struct.g_exit_status = 1;
        return 1;
    }
    else if (args[0])
    {
        // printf("exit\n");
        if (ft_atoi_origin(args[0]) > 256)
            overflow = ft_atoi_origin(args[0]) - 256;
        else
            overflow = ft_atoi_origin(args[0]);
        global_struct.g_exit_status = overflow;
        exit(overflow);
    }
    else
    {
        // printf("exit\n");
        exit(global_struct.g_exit_status);
    }
    // printf("exit\n");
    exit(global_struct.g_exit_status);
}

void freenode(t_list **lst, t_list *node)
{
    t_list *prev;
    if (*lst == node)
        *lst = (*lst)->next;
    else
    {
        prev = *lst;
        while (prev->next != node)
            prev = prev->next;
        prev->next = node->next;
    }

    free(node->key);
    free(node->value);
    free(node->all);
    node->key = NULL;
    node->value = NULL;
    node->all = NULL;
    free(node);
    node = NULL;
}