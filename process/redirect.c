/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:48:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/19 17:20:05 by minkyuki         ###   ########.fr       */
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
// 해당 프로세스의 redirection 정보에 따라 입력/출력 fd 를 반환합니다
// redirection 이 설정되어있지 않으면 fd로 0을 반환합니다
// (프로세스 기준으로 반환하므로 pipe에 적용시 인덱스 처리 주의)

static void	set_input(t_cmd *cmd, int *fd, int unit_cnt)
{
	char	*file_name;
	char	*unit_cnt_tmp;

	if (is_equal(cmd->input[0], "<<"))
	{
		unit_cnt_tmp = ft_itoa(cmd->unit_cnt);
		file_name = ft_strjoin(".heredoc_tmp", unit_cnt_tmp);
		fd[0] = open(file_name, O_RDONLY);
		if (fd[0] < 0)
			exit_err(NULL, file_name, NULL);
		free(unit_cnt_tmp);
		free(file_name);
	}
	else if (is_equal(cmd->input[0], "<"))
	{
		fd[0] = open(cmd->input[1], O_RDONLY);
		if (fd[0] < 0)
			exit_err(NULL, cmd->input[1], NULL);
	}
}

static void	set_output(t_cmd *cmd, int *fd, int unit_cnt)
{
	if (is_equal(cmd->input[0], ">>"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (is_equal(cmd->input[0], ">"))
		fd[1] = open(cmd->input[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
		exit_err(NULL, cmd->input[1], NULL);
}
