/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:12:16 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 11:12:17 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// 사용하고 남은 2차원 배열 처리
void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

/*
 * 큰 또는 작은 따옴표의 내부, 외부인지 확인하는 함수
 * @when	: Parsing, Error check
 * @return	: NONE(0) DQUOTE(1) SQUOTE(2)

 * 환경변수때문에 squote dquote 구분함
 */
int	is_in_quote(char *line, int idx)
{
	int	i;
	int	quote_flag;

	quote_flag = NONE;
	i = -1;
	while (++i < idx)
	{
		if (line[i] == '"')
		{
			if (quote_flag == NONE)
				quote_flag = DQUOTE;
			else
				quote_flag = NONE;
		}
		if (line[i] == '\'')
		{
			if (quote_flag == NONE)
				quote_flag = SQUOTE;
			else
				quote_flag = NONE;
		}
	}
	return (quote_flag);
}

/*
 * check if line[idx] is command or not (> >> < << |)
 * @parameters	: line(tokened line), idx(index to check)
 * @when		: Check is redirection, doubled redir, pipe
 * @return		: NONE(0) PIPE(1) REDIR(2) DOUBLED_REDIR(3)
 */
int	is_cmd(char *line, int idx)
{
	if (!ft_strncmp(line + idx, ">>", 2) || !ft_strncmp(line + idx, "<<", 2))
		return (DOUBLED_REDIR);
	else if (line[idx] == '>' || line[idx] == '<')
		return (REDIR);
	else if (line[idx] == '|')
		return (PIPE);
	else
		return (NONE);
}

// make substr without quotes 
char	*get_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	idx;
	size_t	i;
	int		cnt_quote;

	i = -1;
	idx = -1;
	cnt_quote = 0;
	while (++i < len)
	{
		if (s[start + i] == '\'' || s[start + i] == '"')
			cnt_quote++;
	}
	str = (char *)malloc(sizeof(char) * (len - cnt_quote + 1));
	i = 0;
	while (++idx < len - cnt_quote)
	{
		while (s[start + idx + i] == '\'' || s[start + idx + i] == '"')
			i++;
		str[idx] = (unsigned char)s[start + (unsigned int)idx + i];
	}
	str[idx] = '\0';
	return (str);
}

/*
 * Error 처리 구현중...
 * @when	:1. Check sequence commands and no parameter case
			 2. Check unspecified special characters like \ or ;
			 3. Check smth occurs errors
 * @return	: Error(-1), Pass(0)
*/
int	check_error(char **token)
{
	while (*token)
	{
		if (is_cmd(*token, 0))
		{
			printf("\nchecking...\n");
			printf("token[i] = %s\n", *token);
			token++;
			if (is_cmd(*token, 0) || *token == NULL)
			{
				printf("parse error\n");
				return (-1);
			}
		}
		token++;
	}
	return (0);
}
