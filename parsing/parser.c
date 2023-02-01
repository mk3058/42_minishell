/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:49:48 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 14:49:54 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * cmd 구조체 : [0] input commands, [1] command type, [2] count redirect units, [3] count pipes, [4] next commnad addr.
 * cmd 구조체의 input에 적절히 파싱한 2차원배열 문자열을 저장해야 한다.
 * cmd 구조체의 type에 command type을 지정한다. {word, pipeline, redirect}
 * cmd 구조체에 전체 pipe 개수를 저장한다.
 * 파싱 단계 :
 			1. 한줄 읽기
			1-1. 따옴표 기준 토큰 나누기
			2. 문법 검사 (에러처리) (ex. ;, 리다이렉트 인자가 없는 경우)
			3. 따옴표 안쪽이 아닌 스페이스로 명령 구분
			4. 쌍따옴표 안에서 이스케이프로 작동한 \ 제거
			5. 환경변수($) 고려
*/

#include "../includes/parser.h"

/* 
 * 먼저 따옴표를 확인하며 공백으로 토큰을 나누고 <<, <, >, | 등을 라인별로 확인 후 처리
 * 1. 따옴표를 고려한 공백 기준 토큰화 ok
 * 2. redirect, pipe 기준 토큰화 ok
 * 3. 파싱한 문자들 타입, 유닛, 파이프개수(?) 구조체 리스트에 저장
 * @return	: t_cmd *unit_token (final)
*/
t_cmd	*get_unit_token(char *line)
{
	t_cmd	*cmd = NULL;
	char	**token;
	char	**temp;

	while (*line == ' ')
		line++;
	if (!*line)
		return (0);
	token = get_space_token(line); // parse based on SPACE
	temp = token;
	token = get_cmd_token(temp); // redir, | 기준 토큰화
	free_2d_arr(temp);
	if (check_error(token) < 0)
	{
		free_2d_arr(token);
		return (0);
	}
	temp = token;
	token = check_path(temp);
	free_2d_arr(temp);
	cmd = get_cmd_info(token);
	free_2d_arr(token);
	return (cmd);
}

// initialize cmd list
t_cmd	*get_cmd_info(char **token)
{
	t_cmd	*cmd;
	t_cmd	*head;
	int		p_cnt;

	cmd = cmd_lstinit();
	head = cmd;
	p_cnt = cnt_pipe(token);
	init_input(cmd, token);
	while (cmd)
	{
		init_type(cmd);
		cmd->pipe_cnt = p_cnt;
		cmd = cmd->next;
	}
	return (head);
}

void	init_input(t_cmd *cmd, char **token)
{
	int		i;
	int		unit;

	i = -1;
	unit = 0;
	while (token[++i])
	{
		cmd->unit_cnt = unit;
		if (is_cmd(token[i], 0) > 0) //redirection이 분기가 된다
		{
			cmd->input = ft_2d_strndup(token, i);
			cmd_lstadd(cmd);
			cmd = cmd->next;
			if (is_cmd(token[i], 0) == 1)
			{	
				cmd->input = ft_2d_strndup(token + i, 1);
				cmd_lstadd(cmd);
				cmd = cmd->next;
				unit++;
				i++;
			}
			token += i;
			i = 0;
		}
	}
	cmd->unit_cnt = unit;
	cmd->input = ft_2d_strndup(token, i);
}

void	init_type(t_cmd *cmd)
{
	int		cmd_flag;

	while(cmd)
	{
		cmd_flag = is_cmd(cmd->input[0], 0);
		if (cmd_flag > 0) // type 초기화
		{
			if (cmd_flag == 1)
				cmd->type = pipeline;
			else if (cmd_flag > 1)
				cmd->type = redirect;
			else
				cmd->type = word;
		}
		cmd = cmd->next;
	}
}
