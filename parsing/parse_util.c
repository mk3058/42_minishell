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
