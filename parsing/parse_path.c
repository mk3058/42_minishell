/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:47:12 by bojung            #+#    #+#             */
/*   Updated: 2023/02/08 16:16:29 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/util.h"

int			expand_token(char **token, int dollor_ind);
static int	find_key(char *start, char **key);
static char	*find_env(char *key);

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
				&& token[i][j + 1] != '\'')
			{
				if (i > 0 && is_equal(token[i - 1], "<<"))
					continue ;
				j = expand_token(&token[i], j);
				if (token[i][j] == '\0' || token[i][j] == '$')
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
	if (key_len == 0)
		return (dollor_ind + 1);
	env = find_env(key);
	(*token)[dollor_ind] = '\0';
	res = ft_strjoin(*token, env);
	tmp = res;
	res = ft_strjoin(res, &(*token)[dollor_ind + key_len + 1]);
	free(tmp);
	free(key);
	free(*token);
	free(env);
	*token = res;
	return (dollor_ind + ft_strlen(env));
}

static char	*find_env(char *key)
{
	char	*env;

	if (is_equal(key, "?"))
		env = ft_itoa(*g_env->exit_stat);
	else
	{
		if (get_env(key))
			env = ft_strdup(get_env(key));
		else
			env = ft_strdup("");
	}
	return (env);
}

static int	find_key(char *start, char **key)
{
	int		len;

	len = 0;
	while (ft_isalnum(start[len]) || start[len] == '?' || start[len] == '_')
		len++;
	if (len == 0)
		return (0);
	*key = ft_substr(start, 0, len);
	return (len);
}
