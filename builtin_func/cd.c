/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:15:52 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/24 16:06:22 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd->input[1])
	{
		path = get_env("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = cmd->input[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}
