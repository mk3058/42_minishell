/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:10 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 17:19:45 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"

static void	exec_builtin(t_cmd *cmd);

int	builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int		*std_fd;
	t_cmd	*cur_cmd;

	cur_cmd = find_cur_cmd(cmd, child_num);
	if (cur_cmd == NULL)
		return (1);
	if (cmd->pipe_cnt == 0 && is_builtin(cur_cmd, child_num))
	{
		if (set_redirect(cmd, fd, child_num))
			return (1);
		std_fd = set_fd(fd, proc_cnt, child_num);
		set_handler(print_newline, print_newline);
	}
	exec_builtin(cur_cmd);
	if (cmd->pipe_cnt == 0 && is_builtin(cur_cmd, child_num))
	{
		dup2(std_fd[0], STDIN_FILENO);
		dup2(std_fd[1], STDOUT_FILENO);
		free(std_fd);
	}
	return (is_builtin(cur_cmd, child_num));
}

int	is_builtin(t_cmd *cmd, int child_num)
{
	char	*cmd_input;

	cmd = find_cur_cmd(cmd, child_num);
	if (cmd == NULL)
		return (0);
	cmd_input = cmd->input[0];
	if (is_equal(cmd_input, "cd"))
		return (1);
	else if (is_equal(cmd_input, "echo"))
		return (1);
	else if (is_equal(cmd_input, "env"))
		return (1);
	else if (is_equal(cmd_input, "exit"))
		return (1);
	else if (is_equal(cmd_input, "export"))
		return (1);
	else if (is_equal(cmd_input, "pwd"))
		return (1);
	else if (is_equal(cmd_input, "unset"))
		return (1);
	else
		return (0);
}

static void	exec_builtin(t_cmd *cmd)
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
}
