/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 09:22:32 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/08 17:22:09 by minkyuki         ###   ########.fr       */
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

int	is_minishell(char *input)
{
	int	length;

	length = ft_strlen(input);
	if (length >= 9)
	{
		return (ft_memcmp(input + length - 10, "minishell", 10));
	}
	return (0);
}
