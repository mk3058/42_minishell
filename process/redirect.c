/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:48:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 15:37:34 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static void	set_input(t_cmd *cmd, int *fd, int unit_cnt);
static void	set_output(t_cmd *cmd, int *fd, int unit_cnt);

int	*get_redirect_fd(t_cmd *cmd, int unit_cnt)
{
	int			*fd;

	fd = ft_calloc(2, sizeof(int));
	while (cmd)
	{
		if (cmd->unit_cnt == unit_cnt && cmd->type == redirect)
		{
			set_input(cmd, fd, unit_cnt);
			set_output(cmd, fd, unit_cnt);
		}
		else if (cmd->unit_cnt > unit_cnt)
			break ;
		cmd = cmd->next;
	}
	return (fd);
}

static void	set_input(t_cmd *cmd, int *fd, int unit_cnt)
{
	char	*file_name;
	char	*unit_cnt;

	if (is_equal(cmd->input[0], "<<"))
	{
		unit_cnt = ft_itoa(cmd->unit_cnt);
		file_name = ft_strjoin("here_doc", unit_cnt);
		fd[0] = open(file_name, O_RDONLY);
		free(unit_cnt);
		free(file_name);
	}
	else if (is_equal(cmd->input[0], "<"))
		fd[0] = open(cmd->input[1], O_RDONLY);
}

static void	set_output(t_cmd *cmd, int *fd, int unit_cnt)
{
	if (is_equal(cmd->input[0], ">>"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (is_equal(cmd->input[0], ">"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}
