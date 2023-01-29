/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:15:52 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/29 09:26:30 by minkyu           ###   ########.fr       */
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
			return (print_err("cd: ", "HOME not set\n", NULL, 1));
	}
	else
		path = cmd->input[1];
	if (chdir(path) < 0)
		return (print_err("cd: ", path, ": No such file or directory\n", 1));
	return (0);
}
