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
	while (++i < idx + 1)
	{
		if (line[i] == '"')
		{
			if (quote_flag == NONE)
				quote_flag = DQUOTE;
			else if (quote_flag == DQUOTE)
				quote_flag = NONE;
		}
		else if (line[i] == '\'')
		{
			if (quote_flag == NONE)
				quote_flag = SQUOTE;
			else if (quote_flag == SQUOTE)
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
char	*no_quote_strdup(char *s1)
{
	char	*dup;
	int		len;
	int		i;
	int		dup_idx;

	len = ft_strlen(s1);
	i = -1;
	while (s1[++i])
		if (((s1[i] == '"' && is_in_quote(s1, i) != SQUOTE)
			|| (s1[i] == '\'' && is_in_quote(s1, i) != DQUOTE)))
			len--;
	dup = malloc(sizeof(char) * (len + 1));
	i = 0;
	dup_idx = 0;
	while (s1[i])
	{
		while (((s1[i] == '"' && is_in_quote(s1, i) != SQUOTE) 
			|| (s1[i] == '\'' && is_in_quote(s1, i) != DQUOTE)))
			i++;
		dup[dup_idx] = s1[i];
		i++;
		dup_idx++;
	}
	dup[dup_idx] = '\0';
	return (dup);
}

char	**ft_2d_strndup(char **arr, int	len)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int		cnt_pipe(char **token)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (*token)
	{
		i = 0;
		while ((*token)[i])
		{
			if ((*token)[i] == '|')
				cnt++;
			i++;
		}
		token++;
	}
	return (cnt);
}