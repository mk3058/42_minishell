/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:36:05 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/26 14:30:01 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <sys/errno.h>

# include "../includes/environment.h"
# include "../includes/minishell.h"

int		builtin_controller(t_cmd *cmd, int **fd, int proc_cnt, int child_num);

int		echo(t_cmd *cmd);
int		env(void);
int		export(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		unset(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);

int		is_equal(char *str1, char *str2);
int		builtin_err(char *prefix, char *errmsg, char *postfix, int return_val);
int		is_builtin(t_cmd *cmd);

#endif