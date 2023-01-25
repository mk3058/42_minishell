/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:10 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/25 14:13:42 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	builtin_controller(t_cmd *cmd)
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

builtin 함수 오류 발생 -> stderr로 에러 메시지 출력(파이프라인 사이에서도 fd 바꿔서 출력해야함)
	-> std_fd 백업해서 구조체에 넣어야 할듯?
process 부모 프로세스에서 fd 세팅 오류 발생시 exit 호출돼서 minishell이 종료되는부분 수정 필요
process 오류 메시지 출력 fd stdout->stderr로 수정 필요
malloc_ctl 사용안하면 삭제
