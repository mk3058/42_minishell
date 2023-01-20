/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:50:47 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/20 22:50:24 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	export(t_cmd *cmd)
{
	t_env	*tmp;
	char	*str;

	str = cmd->input[1];
	if (str)
		add_env(str);
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
// 잘못된 option 이 주어지는 경우를 제외하면 반환값은 0 -> minishell 에서는 항상 0
// 인자 없이 export만 입력할 경우 환경변수 내용 출력