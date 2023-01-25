/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/25 12:56:35 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	arg_check(t_cmd *cmd, int cnt);

int	ft_exit(t_cmd *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd->input[cnt])
		cnt++;
	if (arg_check(cmd, cnt))
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cnt == 2)
		*(cmd->exit_stat) = (unsigned char)ft_atoi(cmd->input[1]);
	exit(*(cmd->exit_stat));
}

static int	arg_check(t_cmd *cmd, int cnt)
{
	int	i;

	i = -1;
	while (cnt > 1 && cmd->input[1][++i])
	{
		if (!ft_isdigit(cmd->input[1][i]) && cmd->input[1][i] != '-')
		{
			ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->input[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			*(cmd->exit_stat) = 255;
			exit(*(cmd->exit_stat));
		}
	}
	if (cnt > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
