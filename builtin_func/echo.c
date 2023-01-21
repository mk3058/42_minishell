/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:47:03 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/21 13:51:48 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

// echo -n test         => test%
// echo -nnnnnnnnn test => test%
// echo -nnnnnnnnm test => -nnnnnnnnm test
// echo -m test         => -m test
int	echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = is_option(cmd->input[1]);
	while (cmd->input[++i + flag])
	{
		printf("%s", cmd->input[i + flag]);
		if (cmd->input[i + flag + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}

static int	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}
