/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:55:08 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/06 16:33:39 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

static char		**parse_path(char *cmd);
static void		dealloc(char **env_path);

void	execute_cmd(t_cmd *cmd, int child_num, int **fd)
{
	char	*path;
	t_cmd	*cur_cmd;

	if (set_redirect(cmd, fd, child_num))
		exit(EXIT_FAILURE);
	cur_cmd = find_cur_cmd(cmd, child_num);
	if (cur_cmd == NULL)
		exit(EXIT_SUCCESS);
	if (builtin_controller(cur_cmd, fd, cmd->pipe_cnt + 1, child_num))
		exit(0);
	path = find_path(cur_cmd);
	free(cur_cmd->input[0]);
	cur_cmd->input[0] = ft_strdup(path);
	free(set_fd(fd, cmd->pipe_cnt + 1, child_num));
	if (execve(path, cur_cmd->input, env_to_array()) == -1)
	{
		*(g_env->exit_stat) = err_print(path, ": ", "is a directory", 126);
		exit(*g_env->exit_stat);
	}
}
// 명령어의 위치를 찾고 execve 함수를 호출하여 실행합니다

char	*find_path(t_cmd *cmd)
{
	char	**env_path;
	char	*file_path;
	int		i;

	i = -1;
	if (access(cmd->input[0], R_OK | X_OK) == 0)
		return (ft_strdup(cmd->input[0]));
	env_path = parse_path(cmd->input[0]);
	while (ft_strlen(cmd->input[0]) && env_path && env_path[++i])
	{
		file_path = ft_strjoin(env_path[i], cmd->input[0]);
		if (access(file_path, R_OK | X_OK) == 0)
		{
			dealloc(env_path);
			return (file_path);
		}
		else
			free(file_path);
	}
	if (env_path)
		dealloc(env_path);
	err_print(cmd->input[0], ": command not found", 0, 127);
	*(g_env->exit_stat) = 127;
	exit(EXIT_FAILURE);
}
// 환경변수 경로에 해당 파일이 존재하는지 확인하고 존재하면 경로를 반환합니다
// 경로에서 실행파일을 찾지 못한경우 오류를 출력하고 프로그램을 종료합니다

static char	**parse_path(char *cmd)
{
	char	**parsed_path;
	char	*tmp;
	int		i;

	tmp = get_env("PATH");
	if (tmp == NULL)
	{
		err_print(cmd, ": No such file or directory", 0, 127);
		*g_env->exit_stat = 127;
		exit(*g_env->exit_stat);
	}
	parsed_path = ft_split(tmp, ':');
	i = -1;
	while (parsed_path[++i])
	{
		tmp = parsed_path[i];
		parsed_path[i] = ft_strjoin(parsed_path[i], "/");
		free(tmp);
	}
	return (parsed_path);
}
// 환경변수 리스트에서 주소에 해당하는 부분을 가져와서 콜론 기준으로 분리합니다
// 이후 경로 뒤에 '/' 를 추가합니다

t_cmd	*find_cur_cmd(t_cmd *cmd, int child_num)
{
	while (cmd->unit_cnt < child_num)
		cmd = cmd->next;
	while (cmd && cmd->type != word)
	{
		if (cmd->unit_cnt > child_num)
			return (NULL);
		cmd = cmd->next;
	}
	return (cmd);
}
// cmd list에서 현재 프로세스에서 실행해야할 명령어 파트를 찾아 반환합니다
// 명령어 파트가 없을경우 NULL을 반환합니다

static void	dealloc(char **env_path)
{
	int	i;

	i = -1;
	while (env_path[++i])
		free(env_path[i]);
	free(env_path);
}
