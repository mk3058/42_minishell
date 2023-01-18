/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:58:56 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/18 15:38:27 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd);
static void	wait_proc(int proc_cnt, int *pid, int *statloc);
static void	dealloc(int **fd, t_cmd *cmd);

int	process(t_cmd *cmd, char *envp)
{
	int		**fd;
	int		child_num;
	int		statloc;
	pid_t	*pid;

	child_num = -1;
	heredoc(cmd);
	fd = make_pipe(cmd);
	pid = malloc(sizeof(pid_t) * ((cmd->pipe_cnt) + 1));
	if (fork_proc((cmd->pipe_cnt) + 1, &child_num, pid, fd) != 0)
	{
		close_fd(fd, cmd->pipe_cnt, child_num);
		wait_proc(cmd->pipe_cnt + 1, pid, &statloc);
		dealloc(fd, cmd);
		return (WEXITSTATUS(statloc));
	}
	else
		; //child
	return (0);
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
	;
}
// 사용한 메모리를 정리하고 임시파일을 unlink 합니다 (나중에 구현)




// int main()
// {
// 	t_cmd cmd1, cmd2, cmd3, cmd4, cmd5;

// 	cmd1.input = ft_split("<< EOF", ' ');
// 	cmd1.type = redirect;
// 	cmd1.pipe_cnt = 1;
// 	cmd1.unit_cnt = 0;
// 	cmd1.next = &cmd2;

// 	cmd2.input = ft_split("ls -al", ' ');
// 	cmd2.type = word;
// 	cmd2.pipe_cnt = 1;
// 	cmd2.unit_cnt = 0;
// 	cmd2.next = &cmd3;

// 	cmd3.input = ft_split("|", ' ');
// 	cmd3.type = pipeline;
// 	cmd3.pipe_cnt = 1;
// 	cmd3.unit_cnt = 1;
// 	cmd3.next = &cmd4;

// 	cmd4.input = ft_split("ls -al", ' ');
// 	cmd4.type = word;
// 	cmd4.pipe_cnt = 1;
// 	cmd4.unit_cnt = 2;
// 	cmd4.next = &cmd5;

// 	cmd5.input = ft_split("> outfile", ' ');
// 	cmd5.type = redirect;
// 	cmd5.pipe_cnt = 1;
// 	cmd5.unit_cnt = 2;
// 	cmd5.next = NULL;

// 	process(&cmd1, NULL);
// }