/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:58:21 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/23 14:35:46 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/environment.h"

static int	cnt_key_length(char *env);

int	set_envlist(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		add_env(envp[i++]);
	return (0);
}
//char **형 환경변수를 받아 리스트 형태로 만듦

int	add_env(char *env)
{
	t_env	*tmp;
	int		key_length;

	key_length = cnt_key_length(env);
	if (key_length == 0)
		return (-1);
	tmp = g_env;
	while (tmp)
	{
		if (key_length > 0 && !ft_strncmp(tmp->str, env, key_length + 1))
		{
			free(tmp->str);
			tmp->str = ft_strdup(env);
			return (0);
		}
		else if (key_length < 0 && is_equal(tmp->str, env))
			return (0);
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	tmp->str = ft_strdup(env);
	tmp->next = g_env;
	g_env = tmp;
	return (0);
}
// '='로 시작하는 경우 오류처리 -> -1 반환
// 리스트에 동일한 key가 존재하는 경우 기존 내용을 삭제하고 새로운 변수 할당
// 존재하지 않는 key일경우 새로운 노드를 생성함
// head가 NULL인 경우에는 새로운 노드를 생성함

char	*get_env(char *key)
{
	t_env	*tmp;
	char	*key_tmp;

	tmp = g_env;
	key_tmp = ft_strjoin(key, "=");
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, key, ft_strlen(key)))
		{
			free(key_tmp);
			return ((tmp->str) + ft_strlen(key) + 1);
		}
		tmp = tmp->next;
	}
	free(key_tmp);
	return (NULL);
}
// 환경변수 list에서 key에 해당하는 값을 찾으면 해당 환경변수 반환
// 존재하지 않을경우 NULL 반환

char	**env_to_array(void)
{
	t_env	*tmp;
	char	**envp;
	int		env_cnt;

	tmp = g_env;
	env_cnt = 0;
	while (tmp)
	{
		tmp = tmp->next;
		env_cnt++;
	}
	envp = malloc(sizeof(char *) * (env_cnt + 1));
	tmp = g_env;
	env_cnt = 0;
	while (tmp)
	{
		if (cnt_key_length(tmp->str) > 0)
			envp[env_cnt++] = tmp->str;
		tmp = tmp->next;
	}
	envp[env_cnt] = NULL;
	return (envp);
}
// list 형태의 환경변수를 char ** 형태로 바꾸어 반환
// execve 함수의 인자로 char **envp 가 필요하여 사용
// key = value 형태가 갖춰진 부분만 추가함
// ***str은 리스트의 str을 그대로 사용하므로 해제는 envp 자체만 하면 됨***

static int	cnt_key_length(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
