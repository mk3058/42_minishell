/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:01:30 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 16:25:26 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

int	is_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] - str2[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	cnt_pipe(t_cmd *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd)
	{
		if (cmd->type == pipeline)
			cnt++;
		cmd = cmd->next;
	}
	return (cnt);
}
