/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:17 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/26 14:05:27 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/process.h"

static void	set_redirect(t_cmd *cmd, int **fd);

int	**make_pipe(t_cmd *cmd)
{
	int		**fd;
	int		i;
	t_cmd	*tmp;

	i = -1;
	tmp = cmd;
	fd = malloc(sizeof(int *) * ((cmd->pipe_cnt) + 2));
	while (++i < (cmd->pipe_cnt) + 2)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		if (i == 0)
		{
			close(fd[i][0]);
			fd[i][0] = STDIN_FILENO;
		}
		else if (i == (cmd->pipe_cnt) + 1)
		{
			close(fd[i][1]);
			fd[i][1] = STDOUT_FILENO;
		}
	}
	set_redirect(cmd, fd);
	return (fd);
}
// 프로세스간 통신을 위한 pipe를 개설합니다
// 이후 해당 프로세스에 redirection 이 있는경우 해당 파일로 입/출력을 변경합니다
// fd 배열의 첫번째와 마지막번째는 첫번째와 마지막 프로세스의 입력, 출력을 저장하기 위해서 사용하므로
// fd[0][0], fd[last_ind][1] 만 사용합니다.

static void	set_redirect(t_cmd *cmd, int **fd)
{
	int	i;
	int	*redir_fd;

	i = -1;
	while (++i < cmd->pipe_cnt + 1)
	{
		redir_fd = get_redirect_fd(cmd, i);
		if (redir_fd[0] > 0)
		{
			if (fd[i][0] != STDIN_FILENO)
				close(fd[i][0]);
			fd[i][0] = redir_fd[0];
		}
		if (redir_fd[1] > 0)
		{
			if (fd[i + 1][1] != STDOUT_FILENO)
				close(fd[i + 1][1]);
			fd[i + 1][1] = redir_fd[1];
		}
		free(redir_fd);
	}
}
// 각 프로세스(unit)에 redirection이 존재하는 경우
// pipe에 존재하는 기존 fd를 close하고 redir_fd로 변경합니다
// 기존 fd의 값이 STDIN, STDOUT인 경우 close 하지 않습니다

void	close_fd(int **fd, int proc_cnt, int child_num)
{
	int	i;

	i = -1;
	while (++i <= proc_cnt)
	{
		if (fd[i][1] == STDOUT_FILENO || fd[i][0] == STDIN_FILENO)
			continue ;
		if (i == child_num)
			close(fd[i][1]);
		else if (i == child_num + 1)
			close(fd[i][0]);
		else
		{
			close(fd[i][1]);
			close(fd[i][0]);
		}
	}
}
// 해당 프로세스에서 사용하는 fd를 제외한 불필요한 fd를 close 합니다

int	*set_fd(int **fd, int proc_cnt, int child_num)
{
	int	*std_fd;

	std_fd = malloc(sizeof(int) * 2);
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	close_fd(fd, proc_cnt, child_num);
	dup2(fd[child_num][0], STDIN_FILENO);
	dup2(fd[child_num + 1][1], STDOUT_FILENO);
	return (std_fd);
}
// 해당 프로세스의 입출력 fd를 설정합니다
// STDIN, STDOUT을 반환합니다