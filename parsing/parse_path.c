/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:47:12 by bojung            #+#    #+#             */
/*   Updated: 2023/02/01 11:47:13 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// 환경변수 목록을 체크하고 문자를 변환
char	**check_path(char	**token)
{
	char	**ret;
	int		i;
	int		idx;

	idx = 0;
	ret = cp_create_arr(token);
	while (*token)
	{
		i = 0;
		while ((*token)[i])
		{
			if ((*token)[i] == '$' && is_in_quote(*token, i) != SQUOTE)
				*token = join_path(*token, i);
			i++;
		}
		ret[idx] = no_quote_strdup(*token);
		idx++;
		token++;
	}
	return (ret);
}

char	**cp_create_arr(char **arr)
{
	int		len;
	char	**ret;

	len = 0;
	while (arr[len])
		len++;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	ret[len] = NULL;
	return (ret);
}

char	*join_path(char *str, int i)
{
	char	*path;
	char	*temp;
	int		quote_idx;

	quote_idx = i;
	str[i++] = '\0';
	if (is_in_quote(str, i) == DQUOTE)
	{
		while (str[quote_idx] != '"' && str[quote_idx] != '\'')
			quote_idx++;
		temp = ft_substr(str + quote_idx, 0, ft_strlen(str + quote_idx));
		str[quote_idx] = '\0';
		path = get_env(str + i);
		if (path != NULL)
			str = ft_strjoin(str, path);
		str = ft_strjoin(str, temp);
		free(temp);
	}
	else
	{
		path = get_env(str + i);
		if (path != NULL)
			str = ft_strjoin(str, path);
	}
	return (str);
}
