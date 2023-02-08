/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:12:16 by bojung            #+#    #+#             */
/*   Updated: 2023/02/08 12:24:35 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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

int	is_cmd(char *line, int idx)
{
	if (!line)
		return (-1);
	if (!ft_strncmp(line + idx, ">>", 2) || !ft_strncmp(line + idx, "<<", 2))
		return (DOUBLED_REDIR);
	else if (line[idx] == '>' || line[idx] == '<')
		return (REDIR);
	else if (line[idx] == '|')
		return (PIPE);
	else
		return (NONE);
}

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
	i = -1;
	dup_idx = 0;
	while (s1[++i])
	{
		while (((s1[i] == '"' && is_in_quote(s1, i) != SQUOTE)
				|| (s1[i] == '\'' && is_in_quote(s1, i) != DQUOTE)))
			i++;
		if (s1[i] == '\0')
			break ;
		dup[dup_idx++] = s1[i];
	}
	dup[dup_idx] = '\0';
	return (dup);
}

char	**ft_2d_strndup(char **arr, int len)
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
