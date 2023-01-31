/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:10 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/31 19:38:45 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"

static int	exec_builtin(t_cmd *cmd);

int	builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int	is_builtin;
	int	*std_fd;

	std_fd = set_fd(fd, proc_cnt, child_num);
	if (cmd->pipe_cnt == 0)
		set_handler(print_newline, print_newline);
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
		*(cmd->exit_stat) = cd(cmd);
	else if (is_equal(cmd_input, "echo"))
		*(cmd->exit_stat) = echo(cmd);
	else if (is_equal(cmd_input, "env"))
		*(cmd->exit_stat) = env();
	else if (is_equal(cmd_input, "exit"))
		*(cmd->exit_stat) = ft_exit(cmd);
	else if (is_equal(cmd_input, "export"))
		*(cmd->exit_stat) = export(cmd);
	else if (is_equal(cmd_input, "pwd"))
		*(cmd->exit_stat) = pwd();
	else if (is_equal(cmd_input, "unset"))
		*(cmd->exit_stat) = unset(cmd);
	else
		return (0);
	return (1);
}
