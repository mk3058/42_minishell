/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:27 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 17:20:19 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/environment.h"

static char	*node_to_line(t_env *node);
static int	env_len(void);
int			is_equal(char *str1, char *str2);

char	*get_env(char *key)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**env_to_array(void)
{
	t_env	*tmp;
	char	**envp;
	int		env_idx;

	tmp = g_env;
	env_idx = 0;
	envp = malloc(sizeof(char *) * (env_len() + 1));
	while (tmp)
	{
		if (tmp->value)
			envp[env_idx++] = node_to_line(tmp);
		tmp = tmp->next;
	}
	envp[env_idx] = NULL;
	return (envp);
}

static char	*node_to_line(t_env *node)
{
	char	*line;
	int		size;

	size = ft_strlen(node->key) + ft_strlen(node->value) + 1;
	line = malloc(sizeof(char) * (size + 1));
	line[0] = '\0';
	ft_strlcat(line, node->key, size + 1);
	ft_strlcat(line, "=", size + 1);
	ft_strlcat(line, node->value, size + 1);
	return (line);
}

static int	env_len(void)
{
	t_env	*tmp;
	int		cnt;

	tmp = g_env;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

void	destroy_env(void)
{
	t_env	*next;

	next = NULL;
	free(g_env->exit_stat);
	while (g_env)
	{
		next = g_env->next;
		free(g_env->key);
		free(g_env->value);
		free(g_env);
		g_env = next;
	}
}
