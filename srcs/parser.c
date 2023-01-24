/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:58:34 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 10:58:36 by bojung           ###   ########.fr       */
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

int	cnt_space(char *line)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] != '\0') //마지막에 space가 오는 경우 카운트하지 않음
				cnt++;
		}
		i++;
	}
	return (cnt);
}

// space 단위로 자른 토큰을 2d arr로 반환
char	**get_space_token(char *line)
{
	char	**token;
	int		i;
	int		start;
	int		idx;

	start = 0;
	i = 0;
	idx = 0;
	token = (char **)malloc(sizeof(char *) * (cnt_space(line) + 2));
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			token[idx] = get_substr(line, start, i - start);
			while (line[i] == ' ')
			{
				i++;
				if (line[i] == '\0')
					break ;
			}
			start = i;
			idx++;
		}
		i++;
	}
	if (i > 0)
		token[idx++] = get_substr(line, start, i - start);
	token[idx] = NULL;
	return (token);
}

// redirection, pipe를 추가로 나눈 토큰의 개수를 반환
int	cnt_cmd(char **line)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (*line)
	{
		i = 0;
		cnt++;
		while ((*line)[i] != '\0')
		{
			if(!ft_strncmp(*(line) + i, ">>", 2) || !ft_strncmp(*(line) + i, "<<", 2))
			{
				if (i > 0) // 이전 문자가 존재하면 토큰 개수는 +1
					cnt++;
				if ((*line)[i + 2] != '\0') // 다음 문자가 존재하면 + 1
					cnt++;
				i++;
			}
			else if ((*line)[i] == '>' || (*line)[i] == '<' || (*line)[i] == '|')
			{
				if (i > 0) // 이전 문자가 존재하면 토큰 개수는 +1
					cnt++;
				if ((*line)[i + 1] != '\0') // 다음 문자가 존재하면 + 1
					cnt++;
			}
			i++;
		}
		line++;
	}
	printf("cnt = %d\n", cnt);
	return (cnt);
}

// redirection, pipe를 추가로 나눈 토큰을 반환
// char	**get_cmd_token(char **line)
// {
// 	char	**token;

// 	token = (char **)malloc(sizeof(char *) * cnt_cmd(line) + 1);

// 	return (token);
// }

/* 
 * 먼저 따옴표를 확인하며 공백으로 토큰을 나누고 <<, <, >, | 등을 라인별로 확인 후 처리
 * 1. 따옴표를 고려한 공백 기준 토큰화
 * 2. redirect, pipe 기준 토큰화
 * @return	: **unit_token (final)
 * 개발중
*/
char	**get_unit_token(char *line)
{
	char	**token;
	char	**temp;
	int	i = 0;

	// test용 임시 코드
	while (*line == ' ')
		line++;
	// space 기준 토큰화
	token = get_space_token(line);
	temp = token;

	// redir, | 기준 토큰화
	cnt_cmd(temp);
	//token = get_cmd_token(temp);
	//free_2d_arr(temp);
	while (token[i])
	{
		printf("token[%d] = %s\n", i, token[i]);
		i++;
	}
	return (0);
}
