/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:36:05 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/02 12:21:05 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <sys/errno.h>

# include "../includes/environment.h"
# include "../includes/minishell.h"
# include "../includes/util.h"

int		builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num);
int		is_builtin(t_cmd *cmd);

int		echo(t_cmd *cmd);
int		env(void);
int		export(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		unset(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);

#endif