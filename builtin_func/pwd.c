/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:07:44 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/08 17:20:06 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		perror(NULL);
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
