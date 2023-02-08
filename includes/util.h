/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 17:22:58 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

# include "../libft/libft.h"

int			\
err_print(char *prefix, char *errmsg, char *postfix, int return_val);
int			is_equal(char *str1, char *str2);
int			is_minishell(char *input);

#endif