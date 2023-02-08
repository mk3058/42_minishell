/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:41 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 17:21:08 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static void	heredoc_unit(t_cmd *cmd);
static void	get_input(int fd, char *limiter);
int			expand_token(char **token, int dollor_ind);
static void	heredoc_expander(char **line);

int	heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		statloc;

	set_echoctl(0);
	pid = fork();
	if (pid != 0)
	{
		set_handler(heredoc_quiet, NULL);
		waitpid(pid, &statloc, 0);
		if (WEXITSTATUS(statloc) != 0)
			unlink_file(cmd);
		set_echoctl(1);
	}
	else
	{
		set_handler(heredoc_sigint, NULL);
		heredoc_unit(cmd);
	}
	if (g_env->exit_stat == 0)
		*(g_env->exit_stat) = WEXITSTATUS(statloc);
	return (WEXITSTATUS(statloc));
}

static void	heredoc_unit(t_cmd *cmd)
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
				err_print("heredoc: tmp_err", ": ", strerror(errno), 1);
				break ;
			}
			get_input(fd, cmd->input[1]);
			close(fd);
			free(unit_cnt);
			free(file_name);
		}
		cmd = cmd->next;
	}
	exit(EXIT_SUCCESS);
}

static void	get_input(int fd, char *limiter)
{
	char	*input;
	char	*limiter_tmp;

	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input || is_equal(limiter_tmp, input))
		{
			free(input);
			free(limiter_tmp);
			return ;
		}
		heredoc_expander(&input);
		ft_putstr_fd(input, fd);
		free(input);
	}
}

static void	heredoc_expander(char **line)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_token(line, i);
			if ((*line)[i] == '$')
				i--;
		}
	}
}
