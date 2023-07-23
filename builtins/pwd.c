/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouram < abouram@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:27:32 by shmimi            #+#    #+#             */
/*   Updated: 2023/07/23 19:31:48 by abouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd()
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd");
		global_struct.g_exit_status = 1;
		return ;
	}
	printf("%s\n", pwd);
}
