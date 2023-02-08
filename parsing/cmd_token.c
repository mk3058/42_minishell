/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:59:52 by bojung            #+#    #+#             */
/*   Updated: 2023/01/30 17:57:03 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	cnt_cmd(char **line)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (*line)
	{
		i = -1;
		cnt++;
		while ((*line)[++i] != '\0')
		{
			check_cmd_cnt(*line, &i, &cnt);
		}
		line++;
	}
	return (cnt);
}

void	check_cmd_cnt(char *line, int *i, int *cnt)
{
	if (is_cmd(line, *i) == DOUBLED_REDIR)
	{
		if (*i > 0)
			cnt++;
		if ((line)[++(*i) + 1] != '\0')
			(*cnt)++;
	}
	else if (is_cmd(line, *i) == PIPE || is_cmd(line, *i) == REDIR)
	{
		if (*i > 0)
			(*cnt)++;
		if ((line)[*i + 1] != '\0')
			(*cnt)++;
	}
}

char	**get_cmd_token(char **line)
{
	char	**token;
	int		idx;
	int		i;
	int		start;

	idx = 0;
	token = (char **)malloc(sizeof(char *) * (cnt_cmd(line) + 1));
	while (*line)
	{
		i = -1;
		start = tokenize_cmd(token, *line, i, &idx);
		if ((*line)[start] != '\0')
			token[idx++] = ft_substr(*line, start, ft_strlen(*line) - start);
		line++;
	}
	token[idx] = NULL;
	return (token);
}

int	tokenize_cmd(char **token, char *line, int i, int *idx)
{
	int	start;

	start = 0;
	while (line[++i] != '\0')
	{
		if (!is_in_quote(line, i))
		{
			if (is_cmd(line, i) == DOUBLED_REDIR)
			{
				if (i > 0 && !is_cmd(line, i - 1))
					token[(*idx)++] = ft_substr(line, start, i - start);
				token[(*idx)++] = ft_substr(line, i, 2);
				i++;
				start = i + 1;
			}
			else if (is_cmd(line, i) == PIPE || is_cmd(line, i) == REDIR)
			{
				if (i > 0 && !is_cmd(line, i - 1))
					token[(*idx)++] = ft_substr(line, start, i - start);
				token[(*idx)++] = ft_substr(line, i, 1);
				start = i + 1;
			}
		}
	}
	return (start);
}
