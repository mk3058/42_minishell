/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:58:56 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/29 15:14:28 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd);
static void	wait_proc(int proc_cnt, int *pid, int *statloc);
static void	dealloc(int **fd, t_cmd *cmd);
static void	unlink_file(t_cmd *cmd);

void	process(t_cmd *cmd)
{
	int		**fd;
	int		child_num;
	int		statloc;
	pid_t	*pid;

	child_num = -1;
	if (heredoc(cmd))
		return ;
	fd = make_pipe(cmd);
	if (fd == NULL)
		return ;
	if (cmd->pipe_cnt == 0 && builtin_controller(cmd, fd, 1, 0))
		return ;
	pid = malloc(sizeof(pid_t) * ((cmd->pipe_cnt) + 1));
	if (fork_proc((cmd->pipe_cnt) + 1, &child_num, pid, fd) != 0)
	{
		close_fd(fd, cmd->pipe_cnt + 1, -1);
		wait_proc(cmd->pipe_cnt + 1, pid, &statloc);
		*(cmd->exit_stat) = (WEXITSTATUS(statloc));
		dealloc(fd, cmd);
	}
	else
		execute_cmd(cmd, child_num, fd);
	return ;
}
// 인자로 주어진 cmd 리스트와 환경변수를 바탕으로 프로세스를 분기하여 실행합니다
// builtin 함수가 아닌경우에 호출해서 사용합니다

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd)
{
	if (*child_num >= proc_cnt - 1 || (*child_num >= 0 && pid[*child_num] == 0))
		return (pid[*child_num]);
	(*child_num)++;
	pid[*child_num] = fork();
	return (fork_proc(proc_cnt, child_num, pid, fd));
}
// 프로세스를 생성합니다.

static void	wait_proc(int proc_cnt, int *pid, int *statloc)
{
	int	i;

	i = -1;
	while (++i < proc_cnt)
		waitpid(pid[i], statloc, 0);
}
// 프로세스의 종료상태를 회수하고 마지막 프로세스의 반환값을 인자로 주어진 statloc에 저장합니다

static void	dealloc(int **fd, t_cmd *cmd)
{
	int		i;
	int		cnt;
	t_cmd	*next;

	cnt = cmd->pipe_cnt + 1;
	i = -1;
	unlink_file(cmd);
	while (++i < cnt + 1)
		free(fd[i]);
	free(fd);
	i = -1;
	while (cmd->input[++i])
		free(cmd->input[i]);
	free(cmd->input);
	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
// 사용한 메모리를 정리하고 임시파일을 unlink 합니다

static void	unlink_file(t_cmd *cmd)
{
	int		cnt;
	int		i;
	char	*unit_cnt;
	char	*file_name;

	cnt = cmd->pipe_cnt + 1;
	i = -1;
	while (++i < cnt)
	{
		unit_cnt = ft_itoa(cmd->unit_cnt);
		file_name = ft_strjoin(".heredoc_tmp", unit_cnt);
		if (access(file_name, F_OK) == 0)
			unlink(file_name);
		free(unit_cnt);
		free(file_name);
	}
}
// 생성한 임시파일을 unlink 합니다.
