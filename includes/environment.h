/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:56:17 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 14:59:56 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				*exit_stat;
	struct s_env	*next;
}	t_env;

extern t_env	*g_env;

int		set_envlist(char **envp);
int		add_env(char *env);
char	*get_env(char *key);
char	**env_to_array(void);
void	destroy_env(void);

#endif