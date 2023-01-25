/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:36:05 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/25 12:49:01 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <sys/errno.h>

# include "../includes/environment.h"
# include "../includes/minishell.h"

int		echo(t_cmd *cmd);
int		env(void);
int		export(t_cmd *cmd);
int		pwd(void);
int		cd(t_cmd *cmd);
int		unset(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);

int		is_equal(char *str1, char *str2);
void	builtin_err(char *err_message, char *prefix, char *postfix, int code);

#endif