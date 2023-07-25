/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:27:32 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/25 09:26:04 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd");
		g_global_struct.g_exit_status = 1;
		return ;
	}
	printf("%s\n", pwd);
}
