/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:15:52 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/09 12:18:52 by minkyuki         ###   ########.fr       */
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
			return (err_print("cd: ", "HOME not set", NULL, 1));
	}
	else
		path = cmd->input[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
