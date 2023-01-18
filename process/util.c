/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:01:30 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/18 15:21:52 by minkyuki         ###   ########.fr       */
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

void	exit_err(char *err_message, char *prefix, char *postfix)
{
	if (prefix)
		ft_printf("%s: ", prefix);
	if (err_message)
		ft_printf("%s", err_message);
	else
		ft_printf("%s", strerror(errno));
	if (postfix)
		ft_printf(": %s", postfix);
	ft_printf("\n");
	exit(EXIT_FAILURE);
}
