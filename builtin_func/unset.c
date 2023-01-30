/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:07:43 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/24 16:35:44 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	del_env(char *key);

int	unset(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->input[++i])
		del_env(cmd->input[i]);
	return (0);
}

static void	del_env(char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_env;
	prev = NULL;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
		{
			if (!prev)
				g_env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return ;
}
