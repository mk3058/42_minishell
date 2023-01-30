/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:49:27 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/29 10:53:15 by minkyu           ###   ########.fr       */
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
// 환경변수 list에서 key에 해당하는 값을 찾으면 해당 환경변수 반환
// 존재하지 않거나 value가 없을 경우 NULL 반환

char	**env_to_array(void)
{
	t_env	*tmp;
	char	**envp;
	int		env_idx;

	//*****!! unused variable !!*****
	(void)line;
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
// list 형태의 환경변수를 char ** 형태로 바꾸어 반환
// execve 함수의 인자로 char **envp 가 필요하여 사용
// key = value 형태가 갖춰진 부분만 추가함

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
// node에 저장된 환경변수를 key = value 형태로 바꿔서 반환
// value가 존재하는 경우에만 사용가능

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
