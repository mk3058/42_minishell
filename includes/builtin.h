/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:36:05 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/20 22:51:38 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <sys/errno.h>

# include "../includes/environment.h"
# include "../includes/minishell.h"

int	is_equal(char *str1, char *str2);

#endif