/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:10 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/01 13:03:22 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"

static int	exec_builtin(t_cmd *cmd);

int	builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int	is_builtin;
	int	*std_fd;

	if (cmd->pipe_cnt == 0)
	{
		set_handler(print_newline, print_newline);
		set_redirect(cmd, fd, child_num);
	}
	std_fd = set_fd(fd, proc_cnt, child_num);
	is_builtin = exec_builtin(cmd);
	if (cmd->pipe_cnt == 0)
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
	}
	free(std_fd);
	return (is_builtin);
}

static int	exec_builtin(t_cmd *cmd)
{
	char	*cmd_input;

	cmd_input = cmd->input[0];
	if (is_equal(cmd_input, "cd"))
		*(g_env->exit_stat) = cd(cmd);
	else if (is_equal(cmd_input, "echo"))
		*(g_env->exit_stat) = echo(cmd);
	else if (is_equal(cmd_input, "env"))
		*(g_env->exit_stat) = env();
	else if (is_equal(cmd_input, "exit"))
		*(g_env->exit_stat) = ft_exit(cmd);
	else if (is_equal(cmd_input, "export"))
		*(g_env->exit_stat) = export(cmd);
	else if (is_equal(cmd_input, "pwd"))
		*(g_env->exit_stat) = pwd();
	else if (is_equal(cmd_input, "unset"))
		*(g_env->exit_stat) = unset(cmd);
	else
		return (0);
	return (1);
}
