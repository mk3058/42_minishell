/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:56:17 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/23 13:17:22 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

extern t_env	*g_env;

int		set_envlist(char **envp);
int		add_env(char *env);
char	*get_env(char *key);
char	**env_to_array(void);
void	print_env(void);

int		is_equal(char *str1, char *str2);

#endif