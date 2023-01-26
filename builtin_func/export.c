/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:50:47 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/26 13:26:36 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	print_env(void);

int	export(t_cmd *cmd)
{
	t_env	*tmp;
	char	*str;

	str = cmd->input[1];
	if (str)
	{
		if (add_env(str) < 0)
		{
			builtin_err("export: '", str, "': not a valid identifier\n", 1);
			return (1);
		}
	}
	else
		print_env();
	return (0);
}
// 잘못된 option 이 주어지는 경우를 제외하면 반환값은 0
//	env 첫글자가 영어가 아닐경우 오류
// 인자 없이 export만 입력할 경우 환경변수 내용 출력

static void	print_env(void)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		tmp = tmp->next;
	}
}
// 환경변수를 export 형식에 맞게 출력합니다