/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:19 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 14:52:20 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		space;

	start = 0;
	i = 0;
	idx = 0;
	token = (char **)malloc(sizeof(char *) * (cnt_space(line) + 2));
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			space = 0;
			token[idx] = ft_substr(line, start, i - start);
			while (line[i + space] == ' ')
				space++;
			if (!line[i + space])
				break ;
			i += space;
			start = i;
			idx++;
		}
		i++;
	}
	token[idx] = ft_substr(line, start, i - start);
	token[idx + 1] = NULL;
	return (token);
}
