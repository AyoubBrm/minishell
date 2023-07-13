/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:35:01 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/11 20:16:22 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_n(char *args)
{
    int i = 1;
    // int j = 1;

    while (args[i])
    {
        if (args[i] != 'n')
            return 1;
        i++;
    }
    return 0;
}

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

void my_echo(char **cmd, int exit_status)
{

    int i;
    int flag = 0;
    int lol = 0;
    int blank = 0;
    int j = 2;
    i = 0;

    while (cmd[i])
    {
        if (ft_strncmp(cmd[i], "$?", 2) == 0)
        {
            flag = 1;
            printf("%d", exit_status);
            while (cmd[i][j])
            {
                printf("%c", cmd[i][j]);
                j++;
            }
            if (cmd[i + 1])
                printf(" ");
            j = 2;
        }
        else if (ft_strncmp(cmd[i], "-n", 2) == 0)
        {
            if (!handle_n(cmd[i]) && !cmd[1])
            {
                return;
            }
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
        i++;
    }
    if (!flag && cmd[0])
    {
        lol = get_last_args(cmd);
        while (cmd[lol])
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

void my_cd(char *path, t_list *my_env)
{
    t_list *current = my_env;
    int home_found = 0;
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
            printf("cd: %s: No such file or directory\n", path);
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
        printf("cd: HOME not set\n");
}

char *my_pwd()
{
    int size = 5;
    char *buf = malloc(size);
    while (getcwd(buf, size) == NULL)
    {
        size += size;
        buf = my_realloc(buf, size);
    }
    char *pwd = getcwd(buf, size);
    printf("%s\n", pwd);
    free(buf);
    return pwd;
}

void *my_realloc(char *ptr, int size)
{
    if (ptr == NULL)
        return NULL;
    free(ptr);
    ptr = malloc(size);
    return ptr;
}

void free_env(void *env)
{
    (void)env;
    // t_list *env_var = (t_list *)env;
    // free2d(env_var->all);

    // free(env_var->key);
    // free(env_var->value);
    // free(env_var);
}

t_list *get_env(char **env)
{
    int i = 0;

    t_list *current = NULL;
    t_list *new_env = NULL;
    t_list *head = NULL;

    char **env_old = NULL;
    // char *key = NULL;
    // char *value = NULL;
    while (env[i])
    {
        env_old = ft_split_origin(env[i], '=');
        new_env = malloc(sizeof(t_list));

        new_env->key = NULL;
        new_env->value = NULL;
        new_env->all = NULL;

        new_env->key = ft_strdup(env_old[0]);
        new_env->value = ft_strdup(env_old[1]);
        free2d(env_old);
        new_env->all = ft_strjoin(new_env->key, ft_strchr_inc(env[i], '='));
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
    // printf("heere wtf head %p\n", current);
    while (current)
    {
        if (current->key && ft_strncmp(current->key, "_", 1) == 0)
        {
            free(current->value);
            current->value = ft_strdup("env");
            current->all = ft_strjoin(current->key, "=env");
            printf("%s\n", current->all);
        }
        else if (current->key && current->value && current->all)
            printf("%s\n", current->all);
        current = current->next;
    }
}

t_list *update_env(t_list **my_env)
{
    t_list *current = *my_env;

    while (current)
    {
        printf("WTHHH %p\n", current);
        current = current->next;
    }

    current = *my_env;
    return current;
}

void myexport(char **cmd, t_list *my_env)
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
                my_export->key_exp = ft_strjoin("declare -x ", my_export->key);
                my_export->all = ft_strjoin(my_export->key_exp, my_export->value);
                my_export->next = NULL;
                printf("%s\n", my_export->all);
            }
            else
                printf("declare -x %s\n", my_export->key);
            current = current->next;
            free(my_export->key_exp);
            free(my_export->all);
            free(my_export->key);
            free(my_export->value);
        }
    }
    free(my_export);

    current = my_env;
    int z = 0;

    while (cmd[i])
    {
        while (cmd[i][j])
        {
            if (cmd[i][j] == '+' && cmd[i][j + 1] == '+')
            {
                printf("Minishell: export: `%s': not a valid identifier\n", cmd[i]);
                return;
            }
            else if ((cmd[i][j] == '+' && cmd[i][j + 1] == '=') || cmd[i][j] == '=')
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
                            printf("Minishell: export: `%s': not a valid identifier\n", cmd[i]);
                            free(key);
                            return;
                        }
                    }
                    z++;
                }
            }
            j++;
        }
        i++;
    }
    if (key)
        free(key);

    i = 0;
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
                tmp_key = ft_substr(cmd[i], 0, j);
                key = ft_strdup(tmp_key);
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
                                current->value = ft_strdup(ft_strchr(cmd[i], '='));
                                printf("%p\n", current->value);
                            }
                            if (current->all)
                            {
                                // free(current->key);
                                // free(current->value);
                                free(current->all);
                            }
                            current->all = ft_strjoin(key, current->value);
                            current->next = NULL;
                            printf("%s\n", current->all);
                        }
                        else
                        {
                            free(current->value);
                            current->value = ft_strdup(ft_strchr(cmd[i], '='));
                            current->all = ft_strjoin(key, current->value);
                            current->next = NULL;
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
                    new_export->all = ft_strjoin(key, ft_strchr_inc(cmd[i], '='));
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
                    offset = 0;
                    break;
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
    // while(1);
}

void my_unset(char **to_unset, t_list **my_env)
{
    t_list *current;
    t_list *tmp;

    int i = 0;

    current = *my_env;

    while (to_unset[i])
    {
        printf("to unset %s\n", to_unset[i]);
        while (current)
        {
            if (current->key && ft_strncmp(current->key, to_unset[i], ft_strlen(to_unset[i]) + 1) == 0)
            {
                printf("here\n");
                tmp = current->next;
                freenode(my_env, current);
                current = tmp;
                break;
            }
            if (current)
                current = current->next;
        }
        current = *my_env;
        i++;
    }
}

int my_exit(char **args, int exit_status)
{
    int i = 0;
    int j = 0;
    int overflow = 0;

    while (args[i])
    {
        while (args[i][j])
        {
            if (!ft_isdigit(args[i][j]))
            {
                printf("exit\n");
                printf("minishell: exit: %s: numeric argument required\n", args[i]);
                exit(255);
            }
            j++;
        }
        i++;
        j = 0;
    }

    if (args[0] && args[1])
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return 1;
    }
    else if (args[0])
    {
        printf("exit\n");
        if (ft_atoi_origin(args[0]) > 256)
            overflow = ft_atoi_origin(args[0]) - 256;
        else
            overflow = ft_atoi_origin(args[0]);
        exit_status = overflow;
        exit(overflow);
    }
    else
    {
        printf("exit\n");
        exit(0);
    }
    printf("exit\n");
    exit(exit_status);
}