/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:52:19 by bojung            #+#    #+#             */
/*   Updated: 2023/02/08 12:30:37 by minkyuki         ###   ########.fr       */
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
			if (line[i] == '\0')
				return (cnt);
			cnt++;
		}
		i++;
	}
	return (cnt);
}

char	**get_space_token(char *line)
{
	char	**token;
	int		i;
	int		start;
	int		idx;

	start = 0;
	idx = 0;
	token = (char **)malloc(sizeof(char *) * (cnt_space(line) + 2));
	i = tokenize_space(token, line, &idx, &start);
	if (!line[i])
		token[idx] = ft_substr(line, start, i - start);
	token[idx + 1] = NULL;
	return (token);
}

int	tokenize_space(char **token, char *line, int *idx, int *start)
{
	int	i;
	int	space;

	i = 0;
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			space = 0;
			token[*idx] = ft_substr(line, *start, i - *start);
			while (line[i + space] == ' ')
				space++;
			if (!line[i + space])
				break ;
			i += space;
			*start = i;
			(*idx)++;
		}
		i++;
	}
	return (i);
}
