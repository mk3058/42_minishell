/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:10 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/29 19:56:39 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"

static int	exec_builtin(t_cmd *cmd);
// builtin 함수 오류 발생 -> stderr로 에러 메시지 출력(파이프라인 사이에서도 fd 바꿔서 출력해야함)
// 	-> std_fd 백업해서 구조체에 넣어야 할듯?
// process 부모 프로세스에서 fd 세팅 오류 발생시 exit 호출돼서 minishell이 종료되는부분 수정 필요
// process 오류 메시지 출력 fd stdout->stderr로 수정 필요
// malloc_ctl 사용안하면 삭제

int	builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num)
{
	int	is_builtin;
	int	*std_fd;

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
