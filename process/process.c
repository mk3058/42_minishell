/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:58:56 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/19 17:26:30 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd);
static void	wait_proc(int proc_cnt, int *pid, int *statloc);
static void	dealloc(int **fd, t_cmd *cmd);
static void	unlink_file(t_cmd *cmd);

int	process(t_cmd *cmd)
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
		close_fd(fd, cmd->pipe_cnt + 1, -1);
		wait_proc(cmd->pipe_cnt + 1, pid, &statloc);
		dealloc(fd, cmd);
		return (WEXITSTATUS(statloc));
	}
	else
		execute_cmd(cmd, child_num, fd);
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
	int		i;
	int		cnt;
	char	*file_name;
	t_cmd	*next;

	cnt = cmd->pipe_cnt + 1;
	i = -1;
	unlink_file(cmd);
	while (++i < cnt + 1)
		free(fd[i]);
	free(fd);
	i = -1;
	while (cmd->input[i])
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
		unlink(file_name);
		free(unit_cnt);
		free(file_name);
	}
}
// 생성한 임시파일을 unlink 합니다.


// ********** 테스트를 위한 main입니다 *******************
// t_env *g_env;

// int main(int argc, char **argv, char **envp)
// {
// 	t_cmd cmd1, cmd2, cmd3, cmd4, cmd5, cmd6;

// 	set_envlist(envp);
	
// 	cmd1.input = ft_split("> outfile1", ' ');
// 	cmd1.type = redirect;
// 	cmd1.pipe_cnt = 0;
// 	cmd1.unit_cnt = 0;
// 	cmd1.next = &cmd2;

// 	cmd2.input = ft_split("<< EOF", ' ');
// 	cmd2.type = redirect;
// 	cmd2.pipe_cnt = 0;
// 	cmd2.unit_cnt = 0;
// 	cmd2.next = &cmd3;

// 	cmd3.input = ft_split("grep test", ' ');
// 	cmd3.type = word;
// 	cmd3.pipe_cnt = 0;
// 	cmd3.unit_cnt = 0;
// 	cmd3.next = NULL;

// 	// cmd4.input = ft_split("|", ' ');
// 	// cmd4.type = pipeline;
// 	// cmd4.pipe_cnt = 1;
// 	// cmd4.unit_cnt = 1;
// 	// cmd4.next = &cmd5;

// 	// cmd5.input = ft_split("ls -al", ' ');
// 	// cmd5.type = word;
// 	// cmd5.pipe_cnt = 1;
// 	// cmd5.unit_cnt = 1;
// 	// cmd5.next = &cmd6;

// 	// cmd6.input = ft_split("> outfile2", ' ');
// 	// cmd6.type = redirect;
// 	// cmd6.pipe_cnt = 1;
// 	// cmd6.unit_cnt = 1;
// 	// cmd6.next = NULL;

// 	process(&cmd1);
// }