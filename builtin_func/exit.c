/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/30 17:50:02 by minkyuki         ###   ########.fr       */
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
		*(cmd->exit_stat) = (unsigned char)ft_atoi(cmd->input[1]);
	exit(EXIT_SUCCESS);
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
			*(cmd->exit_stat) = 255;
			exit(*(cmd->exit_stat));
		}
	}
	if (cnt > 2)
		return (err_print("exit: ", "too many arguments", NULL, 1));
	return (0);
}
