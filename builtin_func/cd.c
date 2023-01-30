/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:15:52 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/30 17:49:57 by minkyuki         ###   ########.fr       */
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
		return (err_print("cd: ", path, ": No such file or directory", 1));
	return (0);
}
