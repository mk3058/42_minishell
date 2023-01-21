/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:50:47 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/21 13:33:32 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	export(t_cmd *cmd)
{
	t_env	*tmp;
	char	*str;

	str = cmd->input[1];
	if (str)
	{
		if (add_env(str) < 0)
		{
			printf("export: '%s':  not a valid identifier\n", str);
			return (1);
		}
	}
	else
	{
		tmp = g_env;
		while (tmp)
		{
			printf("declare -x %s\n", tmp->str);
			tmp = tmp->next;
		}
	}
	return (0);
}
// 잘못된 option 이 주어지는 경우를 제외하면 반환값은 0
//	key가 없는 인자가 주어질경우 오류 -> 1반환
// 인자 없이 export만 입력할 경우 환경변수 내용 출력