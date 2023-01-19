/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:55:08 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/19 12:42:19 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/process.h"

void	execute_cmd(t_cmd *cmd, char **envp, int child_num, int **fd)
{
	char	*path;
	int		stdout_backup;

	
}

static char	*find_path(char *cmd, char **envp)
{
	char	**env_path;
	char	*file_path;
	char	*cmd_path;
	int		i;

	if (access(cmd, R_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	
}

static char	**parse_envp(char *envp)
{
	
}
