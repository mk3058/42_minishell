/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:41 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/18 15:35:32 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static void	get_input(int fd, char *limiter);

void	heredoc(t_cmd *cmd)
{
	char	*unit_cnt;
	char	*file_name;
	int		fd;

	while (cmd)
	{
		if (cmd->type == redirect && is_equal(cmd->input[0], "<<"))
		{
			unit_cnt = ft_itoa(cmd->unit_cnt);
			file_name = ft_strjoin(".heredoc_tmp", unit_cnt);
			fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0777);
			if (fd < 0)
				exit_err(NULL, file_name, NULL);
			get_input(fd, cmd->input[1]);
			close(fd);
		}
		cmd = cmd->next;
	}
}

static void	get_input(int fd, char *limiter)
{
	char	*input;
	char	*limiter_tmp;

	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (is_equal(limiter_tmp, input))
		{
			free(input);
			free(limiter_tmp);
			break ;
		}
		ft_putstr_fd(input, fd);
		free(input);
	}
}
