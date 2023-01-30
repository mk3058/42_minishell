/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:48:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/30 12:04:56 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static void	set_input(t_cmd *cmd, int *fd);
static void	set_output(t_cmd *cmd, int *fd);

int	*get_redirect_fd(t_cmd *cmd, int unit_cnt)
{
	int			*fd;

	fd = ft_calloc(2, sizeof(int));
	while (cmd)
	{
		if (cmd->unit_cnt == unit_cnt && cmd->type == redirect)
		{
			set_input(cmd, fd);
			set_output(cmd, fd);
			if (fd[0] < 0 || fd[1] < 0)
			{
				print_err(cmd->input[1], ": ", strerror(errno), 1);
				*(cmd->exit_stat) = 1;
				free(fd);
				return (NULL);
			}
		}
		else if (cmd->unit_cnt > unit_cnt)
			break ;
		cmd = cmd->next;
	}
	return (fd);
}
// 해당 프로세스의 redirection 정보에 따라 입력/출력 fd 를 반환합니다
// redirection 이 설정되어있지 않으면 fd로 0을 반환합니다
// (프로세스 기준으로 반환하므로 pipe에 적용시 인덱스 처리 주의)

static void	set_input(t_cmd *cmd, int *fd)
{
	char	*file_name;
	char	*unit_cnt_tmp;

	if (is_equal(cmd->input[0], "<<"))
	{
		unit_cnt_tmp = ft_itoa(cmd->unit_cnt);
		file_name = ft_strjoin(".heredoc_tmp", unit_cnt_tmp);
		fd[0] = open(file_name, O_RDONLY);
		free(unit_cnt_tmp);
		free(file_name);
	}
	else if (is_equal(cmd->input[0], "<"))
		fd[0] = open(cmd->input[1], O_RDONLY);
}

static void	set_output(t_cmd *cmd, int *fd)
{
	if (is_equal(cmd->input[0], ">>"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (is_equal(cmd->input[0], ">"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}
