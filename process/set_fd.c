/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:17 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 18:12:21 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/process.h"

int	**make_pipe(t_cmd *cmd)
{
	int		pipeline_cnt;
	int		**fd;
	int		i;
	t_cmd	*tmp;

	pipeline_cnt = cnt_pipe(cmd);
	i = -1;
	tmp = cmd;
	fd = malloc(sizeof(int *) * pipeline_cnt + 1);
	while (++i < pipeline_cnt + 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		set_redirect(fd[i], get_redirect_fd(cmd, i));
	}
	return (fd);
}

static void	set_redirect(int *fd, int *redir_fd)
{
	if (redir_fd[0] > 0)
	{
		close(fd[0]);
		fd[0] = redir_fd[0];
	}
	if (redir_fd[1] > 0)
	{
		close(fd[1]);
		fd[1] = redir_fd[1];
	}
}
