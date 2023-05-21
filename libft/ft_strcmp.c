/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:30:32 by shmimi            #+#    #+#             */
/*   Updated: 2023/05/11 16:56:13 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
            i++;
        else
            return 1;
	}
	// if (i < n)
	// 	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
    // printf("%s\n", s1);
    // printf("%s\n", s2);
	return (0);
}