/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/02 21:23:34 by minkyu           ###   ########.fr       */
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
	if (cmd->pipe_cnt == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cnt == 2)
		*(g_env->exit_stat) = (unsigned char)ft_atoi(cmd->input[1]);
	exit(*(g_env->exit_stat));
}

static int	arg_check(t_cmd *cmd, int cnt)
{
	int	i;

	i = -1;
	while (cnt > 1 && cmd->input[1][++i])
	{
		if (!ft_isdigit(cmd->input[1][i]) && cmd->input[1][i] != '-')
		{
			ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
			err_print(0, cmd->input[1], ": numeric argument required", 0);
			*(g_env->exit_stat) = 255;
			exit(*(g_env->exit_stat));
		}
	}
	if (cnt > 2)
		return (err_print("exit: ", "too many arguments", NULL, 1));
	return (0);
}
