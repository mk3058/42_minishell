/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:58:56 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/18 14:03:18 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd);

void	process(t_cmd *cmd, char *envp)
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
		free_all(fd, cmd);
		return (WEXITSTATUS(statloc));
	}
	else
		//child
}

static int	fork_proc(int proc_cnt, int *child_num, pid_t *pid, int **fd)
{
	if (*child_num >= proc_cnt - 1 || (*child_num >= 0 && pid[*child_num] == 0))
		return (pid[*child_num]);
	(*child_num)++;
	pid[*child_num] = fork();
	return (fork_proc(proc_cnt, child_num, pid, fd));
}

static void	wait_proc(int proc_cnt, int *pid, int *statloc)
{
	int	i;

	i = -1;
	while (++i < proc_cnt)
		waitpid(pid[i], statloc, 0);
}

static void	free_all(int **fd, t_cmd *cmd)
{
	;
}
