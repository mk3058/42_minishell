/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:59:52 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 16:59:53 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// redirection, pipe를 추가로 나눈 토큰의 개수를 반환
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
		}
		line++;
	}
	return (cnt);
}

// redirection, pipe를 추가로 나눈 토큰을 반환
char	**get_cmd_token(char **line)
{
	char	**token;
	int		idx;
	int		i;
	int		start;

	idx = 0;
	token = (char **)malloc(sizeof(char *) * cnt_cmd(line) + 1);
	while (*line)
	{
		start = 0;
		i = -1;
		while ((*line)[++i] != '\0')
		{
			if (!is_in_quote(*line, i))
			{
				if(is_cmd(*line, i) == DOUBLED_REDIR)
				{
					if (i > 0 && !is_cmd(*line, i - 1)) // 이전 문자가 존재하면
						token[idx++] = ft_substr(*line, start, i - start);
					token[idx++] = ft_substr(*line, i, 2);
					i++;
					start = i + 1;
				}
				else if (is_cmd(*line, i) == PIPE || is_cmd(*line, i) == REDIR)
				{
					if (i > 0 && !is_cmd(*line, i - 1)) // 이전 문자가 존재하면
						token[idx++] = ft_substr(*line, start, i - start);
					token[idx++] = ft_substr(*line, i, 1);
					start = i + 1;
				}
			}
		}
		if ((*line)[start] != '\0')
			token[idx++] = ft_substr(*line, start, ft_strlen(*line) - start);
		line++;
	}
	return (token);
}
