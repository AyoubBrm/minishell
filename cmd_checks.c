/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:11:55 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/20 18:12:19 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void no_such_file(t_table *current, t_pipes_n_redirection *pipes_n_redirection, int g_exit_status, int i)
{
    if (!current->cmd)
        exit(0);
    if ((access(current->cmd, F_OK | X_OK) < 0 && current->cmd[0] == '/') || (current->cmd[0] == '.' && access(current->cmd, F_OK | X_OK) < 0))
    {
        /************************* Handle > redirection ********************/
        pipes_n_redirection->is_redirected = 0;
        out_redirection(current, pipes_n_redirection, i);
        /************************** End > Redirection ***************************/
        /************************* Handle >> redirection ********************/
        pipes_n_redirection->is_redirected = 0;
        app_redirection(current, pipes_n_redirection, i);
        /************************** End >> Redirection ***************************/
        ft_printf("bash: %s: No such file or directory\n", current->cmd);
        g_exit_status = 127;
        exit(g_exit_status);
    }
    else if (!current->cmd[0] || (!pipes_n_redirection->cmd && current->cmd[0] != '/' && !is_builtin(current->cmd) && access(current->cmd, F_OK | X_OK) < 0))
    {
        /************************* Handle > redirection ********************/
        pipes_n_redirection->is_redirected = 0;
        out_redirection(current, pipes_n_redirection, i);
        /************************** End > Redirection ***************************/
        /************************* Handle >> redirection ********************/
        pipes_n_redirection->is_redirected = 0;
        app_redirection(current, pipes_n_redirection, i);
        /************************** End >> Redirection ***************************/
        int i = 0;
        int flag = 0;
        while (pipes_n_redirection->env2d[i])
        {
            if (ft_strnstr(pipes_n_redirection->env2d[i], "PATH", 4))
            {
                flag = 1;
            }
            i++;
        }
        if (flag)
        {
            ft_printf("bash: %s: command not found\n", current->cmd);
            g_exit_status = 127;
            exit(g_exit_status);
        }
        ft_printf("bash: %s: No such file or directory\n", current->cmd);
        g_exit_status = 127;
        exit(g_exit_status);
    }
}
