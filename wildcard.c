/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:12:36 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/12 00:50:52 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wildcard(char *paths)
{
    DIR *dir = opendir(paths);
    char *path = NULL;
    char *tmp_path;
    int size;

    struct dirent *entry = readdir(dir);

    printf("Here %s\n", paths);

    while (entry)
    {
        printf("%d %s\n", entry->d_type, entry->d_name);
        // if (entry->d_type == 4 && ft_strncmp(entry->d_name, ".", 2) == 0 && ft_strncmp(entry->d_name, "..", 3) == 0)
        // {
        //     // path = my_realloc(path, size);
        //     free(path);
        //     tmp_path = malloc(200);
        //     if (ft_strncmp(paths, ".", 2) != 0 || ft_strncmp(paths, "..", 3) != 0)
        //     {
        //         path = ft_strjoin(tmp_path, paths);
        //         free(tmp_path);
        //     }
        //     tmp_path = ft_strjoin(path, "/");
        //     free(path);
        //     path = ft_strjoin(tmp_path, entry->d_name);
        //     free(tmp_path);
        //     wildcard(path);
        // }
        entry = readdir(dir);
    }
    free(path);
    closedir(dir);
}

void wildcard_helper(t_pipes_n_redirection *pipes_n_redirection)
{
    // pipes_n_redirection->wildcard = ".";
    wildcard(".");
    // while(1);
}