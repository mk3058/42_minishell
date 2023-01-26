/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:01:30 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/26 13:59:17 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

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

void	exit_err(char *err_message, char *prefix, char *postfix)
{
	if (prefix)
		ft_putstr_fd(prefix, STDERR_FILENO);
	if (err_message)
		ft_putstr_fd(err_message, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	if (postfix)
		ft_putstr_fd(postfix, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
// error 상황에서 호출하는 함수입니다.
// prefix와 postfix로 앞, 뒤에 메시지를 추가할 수 있으며 필요하지 않을경우 NULL을 입력합니다
