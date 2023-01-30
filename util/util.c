/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 09:22:32 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/30 17:49:50 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/util.h"

int	err_print(char *prefix, char *errmsg, char *postfix, int return_val)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (prefix)
		ft_putstr_fd(prefix, STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	if (postfix)
		ft_putstr_fd(postfix, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (return_val);
}
// error 상황에서 호출하는 함수입니다.
// prefix와 postfix로 앞, 뒤에 메시지를 추가할 수 있으며 필요하지 않을경우 NULL을 입력합니다
// 인자로 받은 return_val 을 반환합니다

int	is_equal(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] - str2[i] != 0)
			return (0);
		i++;
	}
	return (1);
}
// 두 string이 동일한지 확인하는 함수입니다