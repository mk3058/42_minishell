/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:41 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/01 12:42:43 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static void	get_input(int fd, char *limiter);
static void	heredoc_child(int fd, char *limiter);

int	heredoc(t_cmd *cmd)
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
			{
				err_print(file_name, ": ", strerror(errno), 1);
				*(g_env->exit_stat) = 1;
				return (1);
			}
			get_input(fd, cmd->input[1]);
			close(fd);
			free(unit_cnt);
			free(file_name);
		}
		cmd = cmd->next;
	}
	return (0);
}
// here document 기능 구현부 입니다
// unit별로 heredoc 임시파일을 만들어 사용하며 하나의 유닛에서 여러개의 heredoc 입력을 받을경우 가장 마지막 입력만 처리됩니다

static void	get_input(int fd, char *limiter)
{
	pid_t	pid;
	int		statloc;

	set_echoctl(0);
	pid = fork();
	if (pid != 0)
	{
		set_handler(heredoc_quiet, heredoc_quiet);
		waitpid(pid, &statloc, 0);
		if (*(g_env->exit_stat) == 0)
			*(g_env->exit_stat) = WEXITSTATUS(statloc);
		set_handler(print_prompt, NULL);
	}	
	else
	{
		set_handler(heredoc_sigint, NULL);
		heredoc_child(fd, limiter);
	}
}

static void	heredoc_child(int fd, char *limiter)
{
	char	*input;
	char	*limiter_tmp;

	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
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
