/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:47:12 by bojung            #+#    #+#             */
/*   Updated: 2023/02/06 17:15:20 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/util.h"

int	expand_token(char **token, int dollor_ind);
int	find_key(char *start, char **key);

char	**check_path(char **token)
{
	int	i;
	int	j;

	i = -1;
	while (token[++i])
	{
		j = -1;
		while (token[i][++j])
		{
			if (token[i][j] == '$' && is_in_quote(token[i], j) != SQUOTE
				&& (i > 0 && !is_equal(token[i - 1], "<<")))
			{
				j = expand_token(&token[i], j);
				if (token[i][j - 1] == '$')
					j--;
			}
		}
	}
	return (token);
}

int	expand_token(char **token, int dollor_ind)
{
	char	*key;
	char	*env;
	char	*res;
	char	*tmp;
	int		key_len;

	key_len = find_key((*token) + dollor_ind + 1, &key);
	if (is_equal(key, "?"))
		env = ft_itoa(*g_env->exit_stat);
	else
		env = get_env(key);
	if (env == NULL)
		env = ft_strdup("");
	(*token)[dollor_ind] = '\0';
	res = ft_strjoin(*token, env);
	tmp = res;
	res = ft_strjoin(res, &(*token)[dollor_ind + key_len + 1]);
	free(tmp);
	free(key);
	free(*token);
	*token = res;
	return (dollor_ind + ft_strlen(env) - 1);
}

int	find_key(char *start, char **key)
{
	int		len;

	len = 0;
	while (ft_isalnum(start[len]) || start[len] == '?')
		len++;
	*key = ft_substr(start, 0, len);
	return (len);
}
