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
 * @return	: **unit_token (final)
 * 개발중
*/
char	**get_unit_token(char *line)
{
	char	**token;
	char	**temp;


	while (*line == ' ')
		line++;
	token = get_space_token(line); // parse based on SPACE
	temp = token;
	token = get_cmd_token(temp); // redir, | 기준 토큰화
	//free_2d_arr(temp);

	// test용 임시 코드
	int	i = 0;
	while (token[i])
	{
		printf("token[%d] = %s\n", i, token[i]);
		i++;
	}
	check_error(token);

	return (0);
}
