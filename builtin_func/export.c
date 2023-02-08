/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:50:47 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/08 17:20:02 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	print_env(void);

int	export(t_cmd *cmd)
{
	char	*str;

	str = cmd->input[1];
	if (str)
	{
		if (!ft_isalpha(str[0]))
		{
			err_print("export: '", str, "': not a valid identifier", 1);
			return (1);
		}
		if (add_env(str) < 0)
			return (1);
	}
	else
		print_env();
	return (0);
}

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
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}
