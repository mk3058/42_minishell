/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:47:03 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/20 22:55:56 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	echo(t_cmd *cmd)
{
	int	flag;

	flag = is_equal(cmd->input[1], "-n");
	printf("%s", cmd->input[1 + flag]);
	if (!flag)
		printf("\n");
	return (0);
}
