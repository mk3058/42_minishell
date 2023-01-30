/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:58:21 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/30 17:50:09 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/environment.h"
#include "../includes/builtin.h"

static int	cnt_key_length(char *env);
static void	env_add_back(char *env, int key_length);
int			is_equal(char *str1, char *str2);

int	set_envlist(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		add_env(envp[i]);
		i++;
	}
	return (0);
}
//환경변수를 받아 리스트 형태로 만듦

int	add_env(char *env)
{
	t_env	*tmp;
	int		key_length;

	tmp = g_env;
	key_length = cnt_key_length(env);
	if (key_length == 0)
		return (err_print("setenv ", env, ": Invalid argument", -1));
	if (key_length > 0)
		env[key_length] = '\0';
	while (tmp)
	{
		if (is_equal(tmp->key, env))
		{
			if (key_length > 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(env + key_length + 1);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	env_add_back(env, key_length);
	return (0);
}
// '='로 시작하는 경우 오류처리 -> -1 반환
// 리스트에 동일한 key가 존재하는 경우 기존 내용을 삭제하고 새로운 내용 추가
// 존재하지 않는 key일경우, 리스트가 비어있을 경우 새로운 노드를 생성함
// ****** 인자로 주어지는 env는 수정 가능해야 합니다!! *******

static void	env_add_back(char *env, int key_length)
{
	t_env	*new;
	t_env	*tmp;

	new = ft_calloc(1, sizeof(t_env));
	new->key = ft_strdup(env);
	if (key_length > 0)
	{
		if (!is_equal("SHLVL", new->key))
			new->value = ft_strdup(env + key_length + 1);
		else
			new->value = ft_itoa((ft_atoi(env + key_length + 1) + 1));
	}
	tmp = g_env;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		g_env = new;
}
// 리스트 마지막에 환경변수를 추가함

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
