/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:58:56 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 17:11:26 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static int	fork_proc(int proc_cnt, int *child_cnt, pid_t *pid, int **fd);

void	process(t_cmd *cmd, char *envp)
{
	int		i;
	int		**fd;
	int		child_cnt;
	int		statloc;
	pid_t	*pid;

	i = -1;
	child_cnt = -1;
	heredoc(cmd);
	fd = make_pipe(cmd);
	pid = malloc(sizeof(pid_t) * (cnt_pipe(cmd) + 1));
	if (fork_proc(cnt_pipe(cmd) + 1, &child_cnt, pid, fd) != 0)
	{
		//parent
	}
	else
		//child
}

static int	fork_proc(int proc_cnt, int *child_cnt, pid_t *pid, int **fd)
{
	if (*child_cnt >= proc_cnt - 1 || (*child_cnt >= 0 && pid[*child_cnt] == 0))
		return (pid[*child_cnt]);
	(*child_cnt)++;
	pid[*child_cnt] = fork();
	return (fork_proc(proc_cnt, child_cnt, pid, fd));
}